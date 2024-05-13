#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QWidget>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QDesktopServices>



// 变成单例类
class DataManager : public QWidget
{
    Q_OBJECT



public:
    static DataManager& getInstance();



private:
    DataManager(QWidget* parent = nullptr);

    DataManager(const DataManager&) = delete;

    // 初始化数据库
    bool initDataBase();

    // 查询数据
    int query(QListWidget* listWidget);

    // 添加数据
    void addWidget(const QString& fileName, const QString& fileSize, const QString& dateTime, QListWidget* listWidget);

    // 添加下载记录
    void addDownloadRecord(const QString& fileName, QListWidget* listWidget);

private:
    QSqlDatabase m_database;                        // 数据库对象
    QNetworkAccessManager*  m_httpClient;           // HTTP客户端
    // QListWidget* m_downloadListWidget;              // 下载界面的listWidet
};

#endif // DATAMANAGER_H
