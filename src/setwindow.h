#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include "ClientConfig.hpp"

namespace Ui
{
    class SetWindow;
}

class SetWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SetWindow(QWidget* parent = nullptr);
    ~SetWindow();

private slots:
    // 设置文件的下载目录
    void setDownloadPath(QString dirPath);
    void on_pushButton_change_storage_path_clicked();

private:
    Ui::SetWindow* ui;
};

#endif // SETWINDOW_H
