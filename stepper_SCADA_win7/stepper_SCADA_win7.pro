#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T13:08:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stepper_SCADA_win7
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

# this one must be added @alan.
include ( qextserialport/qextserialport.pri)
