#include "filewindow.h"
#include "ui_filewindow.h"
#include "util.h"
#include "ClientConfig.hpp"
#include "filelistitem.h"


FileWindow::FileWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileWindow)
    , m_httpClient(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // 初始化数据库
    if(!initDataBase())
    {
        QMessageBox::critical(nullptr, "失败", "Can't connect to MysQL server(10051) QMYSQL:无法连接");
    }

    // 当 QListWidget 的 currentItem 变化时，取消新的 currentItem 的焦点 (主要是取消焦点的虚线边框)
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, [this](QListWidgetItem * current, QListWidgetItem*)
    {
        if (current)
        {
            ui->listWidget->clearFocus();
        }
    });

    // 刷新数据 (这里的逻辑和刷新按钮的逻辑一样,只不过当构造函数中刷新数据成功时，不提示用户)

    // 检测网络连接状态
    if(!Util::checkNetworkState())
    {
        QMessageBox::information(nullptr, "提示", "您的网络可能存在问题，请检查一下你的网络");
    }
    else
    {
        int err = this->refreshData();
        // 处理错误
        if(err == DatabaseCanNotOpen)
        {
            QMessageBox::critical(nullptr, "失败", "Can't connect to MysQL server(10051) QMYSQL:无法连接");
        }
        else if(err == QueryError)
        {
            QMessageBox::critical(nullptr, "失败", "数据刷新失败");
        }
    }
}

FileWindow::~FileWindow()
{
    delete ui;
}


int FileWindow::refreshData()
{
    if(!m_database.isOpen())
    {
        // 数据库没有被打开，尝试打开数据库
        if(!m_database.open())
        {
            return DatabaseCanNotOpen;
        }
    }
    return query();
}


/**
 * @brief 上传文件
 */
void FileWindow::uploadFile(QString absolutePath)
{
    if(!absolutePath.isEmpty())
    {
        // 2.打开文件
        QFile* file = new QFile(absolutePath);
        if(file->open(QIODevice::OpenModeFlag::ReadOnly))
        {
            QHttpMultiPart* multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart filePart;
            QFileInfo fileInfo(*file);

            // 3.组织HTTP请求
            filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                               QVariant("form-data; name=\"file\"; filename=\"" + fileInfo.fileName() + "\""));
            filePart.setHeader(QNetworkRequest::ContentTypeHeader,
                               QVariant("application/octet-stream"));
            filePart.setBodyDevice(file);
            multipart->append(filePart);


            // 4.发起HTTP请求
            // QNetworkRequest request(QUrl("http://ipv4.fiddler:8080"));
            QNetworkRequest request(QUrl("http://47.98.187.7:8080/upload"));
            QNetworkReply* response = m_httpClient->post(request, multipart);
            // 当响应销毁时, multipart 一并销毁
            multipart->setParent(response);


            // 5.解析响应
            connect(response, &QNetworkReply::finished, this, [ = ]()
            {
                // 显示提示框
                int statusCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                if(statusCode == 200)
                {
                    QMessageBox::information(nullptr, "成功", "文件上传成功！");
                    // 刷新页面数据
                    this->refreshData();
                }
                else
                {
                    QMessageBox::critical(nullptr, "失败", "文件上传失败！");
                }

                // 清理资源
                response->deleteLater();
                file->close();
                delete file;
            });
        }
    }
}

/**
 * @brief 下载文件
 */
void FileWindow::downloadFile(QString fileName)
{
    // 1.文件名合法性判断
    if(!fileName.isEmpty())
    {
        QUrl url = "http://47.98.187.7:8080/download/" + fileName;
        //2.组织HTTP请求
        QNetworkRequest request(url);

        // 3.打开文件
        QString fileStoragePath = ClientConfig::getInstance().getDownloadPath() + "/" + fileName;
        QFile* file = new QFile(fileStoragePath);
        if (!file->open(QFile::WriteOnly))
        {
            QMessageBox::critical(this, "文件下载失败", file->errorString());
            delete file;
            // 结束函数调用
            return;
        }

        //3.发起HTTP请求
        QNetworkReply* response = m_httpClient->get(request);

        // 4.当数据可以读取时，进行数据读取
        connect(response, &QIODevice::readyRead, this, [file, response]()
        {
            file->write(response->readAll());
        });

        // 5.连接 uploadProgress 信号，发送进度更新的信号。
        connect(response, &QNetworkReply::downloadProgress, this, [ = ](qint64 bytesReceived, qint64 bytesTotal)
        {
            emit this->updateProgressSignal(fileName, bytesReceived, bytesTotal);
        });

        //6.当文件下载完毕时，进行资源释放
        connect(response, &QNetworkReply::finished, this, [ = ]()
        {
            // 读取最后一次数据
            file->write(response->readAll());
            if(response->error())
            {
                QMessageBox::critical(this, "错误", response->errorString());
                // 删除文件
                file->remove();
            }
            // 关闭文件
            file->close();
            delete file;
            // 删除响应
            response->deleteLater();
            // 提示用户
            QMessageBox::information(this, "成功", fileName  + "下载成功！");
        });
    }
}

/**
 * @brief 初始化数据库
 * @return
 */
bool FileWindow::initDataBase()
{
    // 添加一个数据库
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    // 设置数据库的主机号
    m_database.setHostName("47.98.187.7");
    // 设置数据库的端口号
    m_database.setPort(3309);
    // 设置用户名
    m_database.setUserName("client");
    // 设置密码
    m_database.setPassword("pht230531");
    // 设置要操作的数据库名称
    m_database.setDatabaseName("cloud_back");

    // 连接数据库
    return m_database.open();
}

/**
 * @brief 查询数据
 * @return 错误码
 */
int FileWindow::query()
{
    QSqlQuery query("select file_name, last_modify_time, file_size from back_file_info;", m_database);
    if(query.exec())
    {
        // 清除之前的数据
        ui->listWidget->clear();
        // 显示新的数据
        while(query.next())
        {
            // 获取文件名
            QString fileName = query.value(0).toString();
            // 获取文件上传时间
            QString datetime = query.value(1).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            // 获取文件大小
            QString fileSize = Util::convertBytes(query.value(2).toLongLong());
            // 添加数据
            this->addWidget(fileName, fileSize, datetime);
        }
        return NoErrorr;
    }
    else
    {
        QSqlError Error = query.lastError();
        if(Error.type() == QSqlError::StatementError)
        {
            // 数据库没有被打开，尝试重新打开数据库
            // (可能由于断网重连的问题, 这里的报错也很奇怪，QSqlError::StatementError表示sql有问题，但是打印错误信息却显示mysql连接的问题)
            if(!m_database.open())
            {
                return DatabaseCanNotOpen;
            }
            else
            {
                return this->query();
            }
        }
        else
        {
            return QueryError;
        }
    }
}

void FileWindow::addWidget(const QString& fileName, const QString& fileSize, const QString& dateTime)
{
    QListWidgetItem* listWidgetItem = new QListWidgetItem(ui->listWidget);
    listWidgetItem->setSizeHint(QSize(100, 60));

    FileListItem* fileListItem = new FileListItem(fileName, fileSize, dateTime, ui->listWidget);

    // 根据文件名确定文件的图标
    QSvgWidget* svgWidget = Util::getSvgByFile(fileName);

    // 给文件列表子项设置svg图片
    fileListItem->setFileSvg(svgWidget);

    ui->listWidget->setItemWidget(listWidgetItem, fileListItem);

    // 设置点击文件下载按钮,进行文件下载
    QPushButton* btn_download = fileListItem->findChild<QPushButton*>(QString(), Qt::FindChildOption::FindDirectChildrenOnly);
    connect(btn_download, &QPushButton::clicked, this, [ = ]()
    {
        // 检测网络连接状态
        if(!Util::checkNetworkState())
        {
            QMessageBox::information(nullptr, "提示", "您的网络可能存在问题，请检查一下你的网络");
        }
        else
        {
            // 文件下载
            this->downloadFile(fileListItem->getFileName());
            // 发送文件开始下载信号
            emit fileStartDownload(fileName);
        }
    });
}




void FileWindow::on_pushButton_refresh_clicked()
{
    // 检测网络连接状态
    if(!Util::checkNetworkState())
    {
        QMessageBox::information(nullptr, "提示", "您的网络可能存在问题，请检查一下你的网络");
    }
    else
    {
        int err = this->refreshData();
        // 处理错误
        if(err == NoErrorr)
        {
            QMessageBox::information(this, "成功", "数据刷新成功!");
        }
        if(err == DatabaseCanNotOpen)
        {
            QMessageBox::critical(this, "失败", "Can't connect to MysQL server(10051) QMYSQL:无法连接");
        }
        else if(err == QueryError)
        {
            QMessageBox::critical(this, "失败", "数据刷新失败");
        }
    }
}


void FileWindow::on_pushButton_upload_clicked()
{
    // 检测网络连接状态
    if(!Util::checkNetworkState())
    {
        QMessageBox::information(this, "提示", "您的网络可能存在问题，请检查一下你的网络");
    }
    else
    {
        // 1.使用文件选择框选择文件
        QString absolutePath = QFileDialog::getOpenFileName(this);
        if(!absolutePath.isEmpty())
        {
            // 2.上传文件
            this->uploadFile(absolutePath);
        }
    }
}

