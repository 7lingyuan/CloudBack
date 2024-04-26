#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    // 设置应用程序图标
    app.setWindowIcon(QIcon(":/Icon/cloud45.png"));
    // 设置翻译文件为中文
    QTranslator translator;
    if(translator.load(":/translations/qt_zh_CN.qm", QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
    {
        app.installTranslator(&translator);
    }


    MainWindow w;
    w.show();
    return app.exec();
}
