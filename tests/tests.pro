QT += core testlib
QT -= gui

TARGET = tests
TEMPLATE = app
CONFIG +=  console
CONFIG -= app_bundle
CONFIG += desktop

trik {
    QT += multimedia
    DESTDIR = ../trik-build-bin
    OBJECTS_DIR = ../trik-build-bin
    MOC_DIR = ../trik-build-bin
}
desktop {
    CONFIG += mobility
    MOBILITY = multimedia
    INCLUDEPATH += /usr/include/QtMultimediaKit
    INCLUDEPATH += /usr/include/QtMobility

    DEFINES += DESKTOP
}

INCLUDEPATH += ../arm_client/

#include(../arm_client/signal/signal.pri)
#include(../arm_client/recording/recording.pri)

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

# подключаем объектники тестируемых классов
# какие-то жуткие костыли
OBJECTS += $$OUT_PWD/../arm_client/signal.o \
    $$OUT_PWD/../arm_client/sample.o \
    $$OUT_PWD/../arm_client/wavFile.o \
    $$OUT_PWD/../arm_client/soundRecorder.o \
    $$OUT_PWD/../arm_client/moc_soundRecorder.o
