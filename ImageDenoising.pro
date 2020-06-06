greaterThan(QT_MAJOR_VERSION, 4):

QT += widgets
QT += core
QT += gui
QT += network
QT += dbus

TARGET = ImageDenoising
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/denoising.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mainwidget.cpp \
    src/traywidget.cpp \

HEADERS += \
    src/denoising.h \
    src/mainwindow.h \
    src/mainwidget.h \
    src/traywidget.h \

CONFIG += link_pkgconfig c++11 console app_bundle
PKGCONFIG += opencv4


RESOURCES += \
    image.qrc \


