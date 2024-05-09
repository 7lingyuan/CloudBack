#ifndef FileWindow_H
#define FileWindow_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QItemSelectionModel>
#include "ClientConfig.hpp"
#include "util.h"
#include "exception"


namespace Ui
{
    class FileWindow;
}

class FileWindow : public QWidget
{
    Q_OBJECT
public:
    // enum Error
    // {
    //     NoErrorr,
    //     DatabaseNoOpen,

    // };

public:
    explicit FileWindow(QWidget* parent = nullptr);
    ~FileWindow();



private:
    // 刷新数据
    void refreshData();
    // 上传文件
    void uploadFile(QString absolutePath);
    // 下载文件
    void downloadFile(QString FileName);

    // 查询
    void query();

private slots:
    // 刷新数据按钮的槽函数
    void on_pushButton_refresh_clicked();

    // 上传文件按钮的槽函数
    void on_pushButton_upload_clicked();

    // 下载文件按钮的槽函数
    void on_pushButton_download_clicked();

private:
    // 初始化数据库
    bool initDataBase();
    void initTableView();

private:
    Ui::FileWindow* ui;
    QStandardItemModel m_model;                 // 数据模型
    QSqlDatabase m_database;                    // 数据库对象
    QNetworkAccessManager*  m_httpClient;       // HTTP客户端
};

#endif // FileWindow_H
