#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T14:58:22
#
#-------------------------------------------------

QT       += core gui

TARGET = SoundSensor
TEMPLATE = app
CONFIG += mobility
MOBILITY = multimedia

SOURCES += main.cpp\
        testwindow.cpp \
    soundRecorder.cpp \

HEADERS  += testwindow.h \
    soundRecorder.h \

FORMS    += testwindow.ui \

INCLUDEPATH += /usr/include/QtMultimediaKit
INCLUDEPATH += /usr/include/QtMobility
