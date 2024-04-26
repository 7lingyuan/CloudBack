#ifndef TRANSLATIONWINDOW_H
#define TRANSLATIONWINDOW_H

#include <QWidget>

namespace Ui {
class TranslationWindow;
}

class TranslationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TranslationWindow(QWidget *parent = nullptr);
    ~TranslationWindow();

private:
    Ui::TranslationWindow *ui;
};

#endif // TRANSLATIONWINDOW_H
