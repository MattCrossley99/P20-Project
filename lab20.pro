#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    advancedScene.cpp \
    sendWorker.cpp \
    receiveWorker.cpp \
    listenWorker.cpp

HEADERS  += window.h \
    advancedScene.h \
    sendWorker.h \
    receiveWorker.h \
    listenWorker.h

FORMS    += window.ui

LIBS += -L/usr/local/lib -lwiringPi -lpthread


