#-------------------------------------------------
#
# Project created by QtCreator 2013-11-14T17:44:40
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS = -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+

CONFIG +=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChoreBoardA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    task.cpp \
    tasklist.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    task.h \
    tasklist.h \
    test.h


FORMS    += mainwindow.ui
