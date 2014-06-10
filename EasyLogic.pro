#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T17:07:30
#
#-------------------------------------------------

QT       += core gui opengl widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyLogic
TEMPLATE = app

CONFIG += c++11

SOURCES +=\
    src/cell.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/automaton.cpp \
    src/wireworldwidget.cpp \
    src/dataio.cpp \
    src/cellpattern.cpp
    src/mapsettingswindow.cpp \
    src/globals.cpp

HEADERS  += \
    src/mainwindow.h \
    src/cell.h \
    src/globals.h \
    src/automaton.h \
    src/wireworldwidget.h \
    src/dataio.h \
    src/cellpattern.h
    src/mapsettingswindow.h
