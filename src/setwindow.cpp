#include "setwindow.h"
#include "ui_setwindow.h"

#include "ClientConfig.hpp"


SetWindow::SetWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SetWindow)
{
    ui->setupUi(this);

    // 设置下载目录的显示
    ui->lineEdit_storage_path->setPlaceholderText(ClientConfig::getInstance().getDownloadPath());
}

SetWindow::~SetWindow()
{
    delete ui;
}

void SetWindow::setDownloadPath(QString dirPath)
{
    if(!dirPath.isEmpty())
    {
        // 更改下载目录
        ClientConfig::getInstance().setDownloadPath(dirPath);
        // 更改下载目录的显示
        ui->lineEdit_storage_path->setPlaceholderText(ClientConfig::getInstance().getDownloadPath());
    }
}


void SetWindow::on_pushButton_change_storage_path_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if(!dirPath.isEmpty())
    {
        setDownloadPath(dirPath);
    }
}

