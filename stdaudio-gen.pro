#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T14:06:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stdaudio-gen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    note.cpp \
    widgetbarline.cpp \
    widgetnote.cpp

HEADERS  += mainwindow.h \
    note.h \
    widgetbarline.h \
    widgetnote.h

FORMS    += mainwindow.ui
