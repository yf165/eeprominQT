#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T09:30:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eeprominQT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    eeprom.c

HEADERS  += mainwindow.h \
    eeprom.h
