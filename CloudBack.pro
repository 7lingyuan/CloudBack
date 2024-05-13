QT       += core gui network sql network concurrent svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

include($$PWD/src/src.pri)
include($$PWD/lib/lib.pri)

DESTDIR = $$PWD/bin

RESOURCES += \
    resource.qrc \

DESTDIR = $$PWD/bin

RC_FILE = $$PWD/resource/app.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

