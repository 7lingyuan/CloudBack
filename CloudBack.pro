QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include($$PWD/src/src.pri)
include($$PWD/lib/lib.pri)

RESOURCES += \
    resource.qrc \

DESTDIR = $$PWD/bin
