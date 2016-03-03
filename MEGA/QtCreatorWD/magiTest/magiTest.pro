#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T18:17:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_magitest
CONFIG   += console c++14
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_magitest.cpp \
    ../magi/model.cpp \
        ../magi/serialization.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
