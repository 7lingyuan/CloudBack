#ifndef FileWindow_H
#define FileWindow_H

#include <QWidget>

namespace Ui
{
    class FileWindow;
}

class FileWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FileWindow(QWidget* parent = nullptr);
    ~FileWindow();

    void setHtml(const QString& html);

private:
    Ui::FileWindow* ui;
};

#endif // FileWindow_H
