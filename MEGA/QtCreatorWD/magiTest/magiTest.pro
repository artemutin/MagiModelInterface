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

INCLUDEPATH += ../magi
HEADERS += ../magi/model.hpp \
../magi/serialization.hpp \
../magi/experimentmodel.hpp \
../magi/resultmodel.hpp


SOURCES += tst_magitest.cpp \
    ../magi/model.cpp \
        ../magi/serialization.cpp \
        ../magi/experimentmodel.cpp \
        ../magi/resultmodel.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
