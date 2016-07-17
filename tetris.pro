QT += core
QT -= gui

CONFIG += c++11

TARGET = tetris
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    kbhit.h \
    colorful.h \
    ccoordinate.h \
    cblock.h
