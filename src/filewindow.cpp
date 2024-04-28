#include "filewindow.h"
#include "ui_filewindow.h"
#include <QPushButton>

FileWindow::FileWindow(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    // 设置隐藏垂直方向上的表头
    ui->tableWidget->verticalHeader()->hide();
    // 设置不能被编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

FileWindow::~FileWindow()
{
    delete ui;
}

// void FileWindow::setHtml(const QString& html)
// {
//     ui->textBrowserFileInfo->setHtml(html);
// }
