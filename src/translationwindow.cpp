#include "translationwindow.h"
#include "ui_translationwindow.h"

TranslationWindow::TranslationWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TranslationWindow)
{
    ui->setupUi(this);
}

TranslationWindow::~TranslationWindow()
{
    delete ui;
}
