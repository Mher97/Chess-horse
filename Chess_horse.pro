#-------------------------------------------------
#
# Project created by QtCreator 2017-01-20T15:13:16
#
#-------------------------------------------------

QT       += core gui

QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess_horse2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boarditem.cpp \
    boardsquare.cpp \
    controller.cpp \
    boardfigure.cpp

HEADERS  += mainwindow.h \
    const.h \
    boarditem.h \
    boardsquare.h \
    controller.h \
    boardfigure.h

FORMS    += mainwindow.ui

CONFIG   += c++11

