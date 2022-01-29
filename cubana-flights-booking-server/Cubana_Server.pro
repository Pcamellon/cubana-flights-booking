#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T13:30:29
#
#-------------------------------------------------

QT       += core gui sql network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cubana_Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mod.cpp

HEADERS  += mainwindow.h \
    mod.h

FORMS    += mainwindow.ui \
    mod.ui
