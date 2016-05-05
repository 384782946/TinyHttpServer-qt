#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T12:00:28
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = TinyHttpServer
TEMPLATE = app

CONFIG  += c++11


SOURCES += src/main.cpp\
        src/OptionWidget.cpp \
    src/mongoose.c \
    src/WebServer.cpp \
    src/TrayMenu.cpp

HEADERS  += src/OptionWidget.hpp \
    src/mongoose.h \
    src/WebServer.hpp \
    src/TrayMenu.hpp

RESOURCES += qrc.qrc
