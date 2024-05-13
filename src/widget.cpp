#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("简易云盘");
    this->setupStackedWidget();

    // 对按钮进行分组
    QButtonGroup* buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);

    buttonGroup->addButton(ui->toolButton_file_list, 0);
    buttonGroup->addButton(ui->toolButton_download, 1);
    buttonGroup->addButton(ui->toolButton_settings, 2);

    // 按钮组的按钮被点击信号后， stackedWidget切换界面
    connect(buttonGroup, &QButtonGroup::idClicked, ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    // 当收到文件下载按钮时，在下载记录页面添加新的下载记录
    connect(page_file, &FileWindow::fileStartDownload, page_download, &DownloadWindow::addDownloadItem);

    // 当收到文件下载进度更新按钮时,在下载界面更新下载进度条
    connect(page_file, &FileWindow::updateProgressSignal, page_download, &DownloadWindow::updateProgress);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::setupStackedWidget()
{
    page_file = new FileWindow(this);
    page_download = new DownloadWindow (this);
    page_set = new SetWindow(this);

    // 向多页窗口添加页面
    ui->stackedWidget->addWidget(page_file);
    ui->stackedWidget->addWidget(page_download);
    ui->stackedWidget->addWidget(page_set);

    ui->stackedWidget->setCurrentIndex(0);                               // 默认显示第一页
}
