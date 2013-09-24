QT += core testlib
QT -= gui

TARGET = tests
TEMPLATE = app
CONFIG +=  console
CONFIG -= app_bundle

include(../defines.pri)

DESTDIR = $$BUILD_FOLDER/tests
OBJECTS_DIR = $$BUILD_FOLDER/tests
MOC_DIR = $$BUILD_FOLDER/tests
RCC_DIR = $$BUILD_FOLDER/tests
UI_DIR = $$BUILD_FOLDER/tests

INCLUDEPATH += ../arm_client/

HEADERS += \
    arm_client/recording/wavFileTest.h \
    arm_client/signal/signalTest.h \
    arm_client/signal/sampleTest.h \
    arm_client/recording/recordtest.h \
    tests.h

SOURCES += \
    main.cpp \
    arm_client/recording/recordtest.cpp \
    tests.cpp

OBJ_PATH = $$BUILD_FOLDER/arm_client
OBJECTS += $$OBJ_PATH/signal.o \
    $$OBJ_PATH/sample.o \
    $$OBJ_PATH/wavFile.o \
    $$OBJ_PATH/soundRecorder.o \
    $$OBJ_PATH/moc_soundRecorder.o
