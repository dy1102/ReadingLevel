#-------------------------------------------------
#
# Project created by QtCreator 2013-08-15T17:00:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    mydialog.cpp

HEADERS  += mywidget.h \
    mydialog.h

FORMS    += mywidget.ui \
    mydialog.ui

CONFIG += mobility
MOBILITY = 

