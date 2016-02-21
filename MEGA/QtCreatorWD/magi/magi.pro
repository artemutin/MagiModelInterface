#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T22:56:01
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = magi
TEMPLATE = app


SOURCES += mainwindow.cpp \
    model.cpp \
    main.cpp

HEADERS  += mainwindow.hpp \
    model.hpp

FORMS    += mainwindow.ui

CONFIG += c++14
