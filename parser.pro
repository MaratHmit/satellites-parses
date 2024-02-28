#-------------------------------------------------
#
# Project created by QtCreator 2024-02-26T10:18:06
#
#-------------------------------------------------

QT       += core
QT       += gui

TARGET = parser
CONFIG   += console
CONFIG   += app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    reader/reader.cpp \
    handler/handler.cpp \
    reader/satellitesinfo.cpp \
    handler/printer.cpp

HEADERS += \
    reader/satellite.h \
    handler/consts.h \
    reader/reader.h \
    handler/handler.h \
    reader/satellitesinfo.h \
    handler/printer.h

INCLUDEPATH += $$PWD \
    $$PWD/reader \
    $$PWD/handler \

CONFIG += c++11

