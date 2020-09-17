TEMPLATE = app
TARGET = 2048
QT += qml quick widgets
DESTDIR = ../2048/bin

HEADERS += \
    src/Controller.h \
    src/Config.h

SOURCES += \
    src/main.cpp \
    src/Controller.cpp

RESOURCES += \
    res/image/image.qrc \
    res/qml/qml.qrc
