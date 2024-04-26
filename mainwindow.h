#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "filewindow.h"
#include "translationwindow.h"
#include "personwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    // 文件显示按钮槽函数
    void on_toolButtonFile_clicked();

private:
    void initWindow();

private:
    Ui::MainWindow* ui;

    // 按钮分组管理
    QButtonGroup* m_buttonGroup;

    // 文件窗口
    FileWindow* m_FileWindow;

    // 传输窗口
    TranslationWindow* m_translationWindow;

    // 个人中心窗口
    PersonWindow* m_personWindow;

    // HTTP请求对象
    QNetworkAccessManager* m_httpClient;

};
#endif // MAINWINDOW_H
