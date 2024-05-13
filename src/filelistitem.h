#ifndef FILELISTITEM_H
#define FILELISTITEM_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QString>
#include <QtSvgWidgets/QSvgWidget>


class FileListItem : public QWidget
{
    Q_OBJECT
public:
    explicit FileListItem(QWidget* parent = nullptr);
    FileListItem(const QString fileName, const QString fileSize, const QString dateTime, QWidget* parent);

    // 设置图标
    void setFileSvg(QSvgWidget* svgWidget);

    // 设置文件名
    void setFileName(const QString& fileName);

    // 设置文件大小
    void setFileSize(const QString& fileszie);

    // 设置文件上传时间
    void setDataTime(const QString& datatime);

    // 得到文件名称
    const QString getFileName() const;

    ~FileListItem();

private:

    QSvgWidget* m_fileSvg;                              // 文件图标
    QLabel m_fileName;                                  // 文件名展示
    QLabel m_fileSize;                                  // 文件大小
    QLabel m_datetime;                                  // 文件上传时间

    QPushButton* m_btn_download;                        // 文件下载按钮
};

#endif // FILELISTITEM_H
