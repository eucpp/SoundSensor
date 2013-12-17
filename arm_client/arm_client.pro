#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T14:58:22
#
#-------------------------------------------------


# общие настройки qt проекта
QT       += core
QT -= gui
TARGET = arm_client
TEMPLATE = app
CONFIG +=  console
CONFIG -= app_bundle

include(../defines.pri)


# подключаем подпроекты
include(signal/signal.pri)
include(recording/recording.pri)
include(codecEngineWrap/codecEngineWrap.pri)


SOURCES += main.cpp \
    tests.cpp

DESTDIR = $$BUILD_FOLDER/arm_client
OBJECTS_DIR = $$BUILD_FOLDER/arm_client
MOC_DIR = $$BUILD_FOLDER/arm_client
RCC_DIR = $$BUILD_FOLDER/arm_client
UI_DIR = $$BUILD_FOLDER/arm_client

HEADERS += \
    tests.h
