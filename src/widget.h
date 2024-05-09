#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include "filewindow.h"
#include "setwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    // 设置stackWidget界面
    void setupStackedWidget();

private:
    FileWindow* page_file;                      // 文件窗口
    QWidget*    page_record;                    // 下载记录
    SetWindow* page_set;                        // 设置页
    Ui::Widget* ui;                             // ui界面
};
#endif // WIDGET_H
