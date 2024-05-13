#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H

#include <QWidget>
#include <QFileInfo>
#include <QDesktopServices>
#include <QListWidget>
#include <QHBoxLayout>

namespace Ui
{
    class DownloadWindow;
}

class DownloadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadWindow(QWidget* parent = nullptr);
    ~DownloadWindow();

    // 添加下载记录
    void addDownloadItem(const QString& fileName);

    // 更新进度条
    void updateProgress(const QString& fileName, qint64 bytesReceived, qint64 bytesTotal);

private:
    QWidget* m_recordWidget;
    QListWidget* m_listWidget;                               // 文件信息列表
};

#endif // DOWNLOADWINDOW_H
