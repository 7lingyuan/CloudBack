#include "filewindow.h"
#include "ui_filewindow.h"
#include <QGridLayout>

FileWindow::FileWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileWindow)
{
    ui->setupUi(this);

    // 1.添加布局管理
    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->addWidget(ui->textBrowserFileInfo, 0, 0);
    gridLayout->addWidget(ui->pushButtonUpload, 1, 0);
    gridLayout->addWidget(ui->pushButtonDownload, 1, 1);
}

FileWindow::~FileWindow()
{
    delete ui;
}

void FileWindow::setHtml(const QString& html)
{
    ui->textBrowserFileInfo->setHtml(html);
}
