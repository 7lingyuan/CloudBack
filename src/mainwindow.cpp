#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QOverload>
#include <QMessageBox>

const char server_ip[] = "47.98.187.7";
const quint16 server_port = 8080;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_buttonGroup(new QButtonGroup(this))
    , m_FileWindow(new FileWindow(this))
    , m_translationWindow(new TranslationWindow(this))
    , m_personWindow(new PersonWindow(this))
    , m_httpClient(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // 1.初始化主窗口
    this->initWindow();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{
    // 1.设置窗口标题
    this->setWindowTitle("简易云盘");

    // 2.设置窗口布局的外边距为0
    ui->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);


    QPixmap pixmap(":/Icon/cloud43.png");
    ui->labelIcon->setPixmap(pixmap);

    // 4.添加侧边栏窗口
    ui->stackedWidget->addWidget(m_FileWindow);
    ui->stackedWidget->addWidget(m_translationWindow);
    ui->stackedWidget->addWidget(m_personWindow);

    // 5.给每个按钮分配编号
    m_buttonGroup->addButton(ui->toolButtonFile, 0);
    m_buttonGroup->addButton(ui->toolButtonTranslation, 1);
    m_buttonGroup->addButton(ui->toolButtonPerson, 2);


    // 6.设置信号槽，当按钮被点击时进行页面切换
    connect(m_buttonGroup, &QButtonGroup::idClicked,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    // 7.设置默认选中的页面
    m_buttonGroup->button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_toolButtonFile_clicked()
{
    // 1.构造HTTP请求
    QUrl url(QString("http://%1:%2").arg(server_ip).arg(server_port));
    // QUrl url("http://www.baidu.com");
    QNetworkRequest request(url);
    // 2.发起HTTP请求
    QNetworkReply* response = m_httpClient->get(request);

    // 3.通过信号槽来处理响应
    connect(response, &QNetworkReply::finished, this, [ = ]()
    {
        // 1.延时删除response
        response->deleteLater();
        // 2.将响应进行显示
        if(response->error() == QNetworkReply::NoError)
        {
            QString html = response->readAll();
            m_FileWindow->setHtml(html);
        }
        else
        {
            // 当显示文件列表操作失败时，直接退出程序
            QMessageBox::critical(this, "客户端接收响应失败", response->errorString());
        }
    });
}

