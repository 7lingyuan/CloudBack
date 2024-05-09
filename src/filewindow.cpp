#include "filewindow.h"
#include "ui_filewindow.h"

FileWindow::FileWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileWindow)
    , m_httpClient(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // 初始化数据表
    initTableView();

    // 初始化数据库
    if(initDataBase())
    {
        // 刷新数据
        refreshData();
    }
    else
    {
        QMessageBox::critical(this, "失败", "Can't connect to MysQL server(10051) QMYSQL:无法连接");
    }
}

FileWindow::~FileWindow()
{
    delete m_httpClient;
    delete ui;
}



/**
 * @brief 刷新页面显示的数据
 * @return
 */
void FileWindow::refreshData()
{
    if(!m_database.isOpen())
    {
        // 数据库没有被打开，尝试打开数据库
        if(!m_database.open())
        {
            QMessageBox::critical(this, "失败", "Can't connect to MysQL server(10051) QMYSQL:无法连接");
        }
    }
    query();
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
            multipart->setParent(response);


            // 5.解析响应
            connect(response, &QNetworkReply::finished, this, [this, file, response]()
            {
                // 显示提示框
                int statusCode = response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                if(statusCode == 200)
                {
                    QMessageBox::information(this, "成功", "文件上传成功！");
                    // 刷新页面数据
                    this->refreshData();
                }
                else
                {
                    QMessageBox::critical(this, "失败", "文件上传失败！");
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

        // 5.连接 downloadProgress 信号，更新进度条的值。
        /*        connect(response, &QNetworkReply::uploadProgress, this, [](qint64 bytesReceived, qint64 bytesTotal){

                })*/;

        //6.当文件下载完毕时，进行资源释放
        connect(response, &QNetworkReply::finished, this, [this, response, file]()
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
            QMessageBox::information(this, "成功", "文件下载成功！");
        });
    }
}

void FileWindow::query()
{
    static bool isFirst = true;
    QSqlQuery query("select file_name, last_modify_time, file_size from back_file_info;", m_database);
    if(query.exec())
    {
        // 清除之前的数据
        m_model.removeRows(0, m_model.rowCount());
        // 显示新的数据
        while(query.next())
        {
            QList<QStandardItem*> items;
            // 获取文件名
            items.push_back(new QStandardItem(query.value(0).toString()));
            // 将时间类型进行转化
            QString datatime = query.value(1).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            items.push_back(new QStandardItem(datatime));
            // 获取文件大小
            qint64 file_size  = query.value(2).toLongLong();
            items.push_back(new QStandardItem(Util::convertBytes(file_size)));
            m_model.appendRow(items);
        }
        if(!isFirst)
        {
            QMessageBox::information(this, "成功", "数据刷新成功！");
        }
        else
        {
            isFirst = false;
        }
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
                QMessageBox::critical(this, "失败", "Can't connect to MysQL server(10051) QMYSQL:无法连接");
            }
            else
            {
                this->query();
            }
        }
        else
        {
            QMessageBox::critical(this, "失败", Error.text());
        }
    }
}


/**
 * @brief 刷新按钮的槽函数
 */
void FileWindow::on_pushButton_refresh_clicked()
{
    // 检测网络连接状态
    if(!Util::checkNetworkState())
    {
        QMessageBox::information(this, "提示", "您的网络可能存在问题，请检查一下你的网络");
    }
    else
    {
        refreshData();
    }
}

/**
 * @brief 上传文件按钮的槽函数
 */
void FileWindow::on_pushButton_upload_clicked()
{
    // 1.使用文件选择框选择文件
    QString absolutePath = QFileDialog::getOpenFileName(this);
    if(!absolutePath.isEmpty())
    {
        // 2.上传文件
        uploadFile(absolutePath);
    }
}

/**
 * @brief 下载文件按钮的槽函数
 */
void FileWindow::on_pushButton_download_clicked()
{
    //1.得到选择模型
    QItemSelectionModel* selection = ui->tableView->selectionModel();
    QModelIndexList selectedRows = selection->selectedRows();

    //2.得到文件名称
    for(const QModelIndex& index : selectedRows)
    {
        QString fileName = index.data().toString();
        // 3.文件下载
        downloadFile(fileName);
    }
}

/**
 * @brief 初始化TableView
 */
void FileWindow::initTableView()
{
    // 设置数据模型
    ui->tableView->setModel(&m_model);
    // 设置数据不能被编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 设置表头自动填充可用空间大小
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 设置选择模式为行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 设置只能选择一行
    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    // 设置表头
    m_model.setHorizontalHeaderLabels(QStringList{"文件名", "上传时间", "文件大小"});
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




