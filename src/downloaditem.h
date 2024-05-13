#ifndef DOWNLOADITEM_H
#define DOWNLOADITEM_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QListWidget>
#include <QString>
#include <QSvgWidget>


class DownloadItem : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadItem(QWidget* parent = nullptr);
    explicit DownloadItem(QString fileName, QWidget* parent = nullptr);

    // 设置图标
    void setFileSvg(QSvgWidget* svgWidget);

    // 设置文件名
    void setFileName(const QString& fileName);

    // 获得真实文件名
    const QString getFileName() const;

    // 获得文件的下载路径
    const QString& getDownlaodPath() const;

    // 设置进度条的进度
    void setProgressBarValue(int value);

private:
    QSvgWidget* m_fileSvg;                              // 文件图标
    QLabel m_fileName;                                  // 文件名展示

    QProgressBar m_progressBar;                         // 进度条
    QPushButton* m_btn_folder;                          // 文件打开按钮
    QString m_downloadPath;                             // 文件的下载路径
};

#endif // DOWNLOADITEM_H
