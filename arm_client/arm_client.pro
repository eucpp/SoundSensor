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

CONFIG += trik
trik {
    message("Building for Trik")

    QT += multimedia


    DEFINES += TRIK
}


# подключаем подпроекты
include(signal/signal.pri)
include(recording/recording.pri)
include(codecEngineWrap/codecEngineWrap.pri)


SOURCES += main.cpp \
    tests.cpp

#DESTDIR = $$BUILD_FOLDER/arm_client
#OBJECTS_DIR = $$BUILD_FOLDER/arm_client
#MOC_DIR = $$BUILD_FOLDER/arm_client
#RCC_DIR = $$BUILD_FOLDER/arm_client
#UI_DIR = $$BUILD_FOLDER/arm_client

HEADERS += \
    tests.h


unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += "'libcodecengine-client >= 0.0.1'"

    target.path = $$[INSTALL_ROOT]/bin
    INSTALLS += target

    QMAKE_CXXFLAGS += -std=c++0x -Wno-unused-parameter
}



INCLUDEPATH += include/

#INCLUDEPATH += /opt/trik-dsp/xdctools_3_24_07_73/packages \
#    /opt/trik-dsp/xdais_7_23_00_06/packages \
#    /opt/trik-dsp/codec_engine_3_23_00_07/packages \
#    /opt/trik-dsp/dsplib_3_1_1_1/packages \
#    /opt/trik-dsp/framework_components_3_23_03_17/packages \
#    /opt/trik-dsp/osal_1_23_00_04/packages \
#    /opt/trik-dsp/linuxutils_3_23_00_01/packages \
#    /opt/trik-dsp/syslink_2_21_01_05/packages
