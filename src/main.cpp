#include "widget.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QMessageBox>




int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    // 设置应用程序图标
    app.setWindowIcon(QIcon(":/resource/Icon/cloud.png"));
    // 设置翻译文件为中文
    QTranslator translator;
    if(translator.load(":/resource/translations/qt_zh_CN.qm", QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
    {
        app.installTranslator(&translator);
    }

    Widget w;
    w.show();
    return app.exec();
}
