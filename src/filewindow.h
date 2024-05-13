#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QFontMetrics>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>



QT_BEGIN_NAMESPACE
namespace Ui
{
    class FileWindow;
}
QT_END_NAMESPACE

class FileWindow : public QWidget
{
    Q_OBJECT

public:
    enum Error
    {
        NoErrorr,
        DatabaseCanNotOpen,
        QueryError
    };

public:
    FileWindow(QWidget* parent = nullptr);
    ~FileWindow();

signals:
    // 文件开始下载信号
    void fileStartDownload(const QString& fileName);
    // 更新进度条信号
    void updateProgressSignal(const QString& fileName, qint64 bytesReceived, qint64 bytesTotal);

private:
    // 刷新数据
    int refreshData();
    // 上传文件
    void uploadFile(QString absolutePath);
    // 下载文件
    void downloadFile(QString fileName);


private slots:
    // 刷新按钮的槽函数
    void on_pushButton_refresh_clicked();
    // 上传按钮的槽函数
    void on_pushButton_upload_clicked();

    // 初始化数据库
    bool initDataBase();

    // 查询数据
    int query();

    // 添加数据
    void addWidget(const QString& fileName, const QString& fileSize, const QString& dateTime);
private:
    Ui::FileWindow* ui;                                         // 界面ui
    QSqlDatabase m_database;                                    // 数据库对象
    QNetworkAccessManager*  m_httpClient;                       // HTTP客户端
};
#endif // FILEWINDOW_H

