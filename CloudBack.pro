QT       += core gui network sql network concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include($$PWD/src/src.pri)
include($$PWD/lib/lib.pri)

DESTDIR = $$PWD/bin

RESOURCES += \
    resource.qrc \

DESTDIR = $$PWD/bin

RC_FILE = $$PWD/resource/app.rc
