#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T11:20:28
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport
QT       += multimedia
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
RC_ICONS = appico.ico

TARGET = BeaconControlCenter
TEMPLATE = app


SOURCES += main.cpp \
    BeaconControlCenter.cpp \
    FramelessWindow.cpp \
    FramelessWindowCentralWidget.cpp

HEADERS  += \
    BeaconControlCenter.h \
    FramelessWindow.h \
    FramelessWindowCentralWidget.h \
    stable.h

FORMS    += beaconcontrolcenter.ui \
    FramelessWindowCentralWidget.ui

RESOURCES += \
    res.qrc

PRECOMPILED_HEADER = stable.h
QMAKE_CFLAGS_RELEASE =-Os -momit-leaf-frame-pointer
