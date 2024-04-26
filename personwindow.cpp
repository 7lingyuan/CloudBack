#include "personwindow.h"
#include "ui_personwindow.h"

PersonWindow::PersonWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PersonWindow)
{
    ui->setupUi(this);
}

PersonWindow::~PersonWindow()
{
    delete ui;
}
