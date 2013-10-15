QT += core testlib
QT -= gui

TARGET = tests
TEMPLATE = app
CONFIG +=  console
CONFIG -= app_bundle

DEFINES += TEST

include(../defines.pri)

DESTDIR = $$BUILD_FOLDER/tests
OBJECTS_DIR = $$BUILD_FOLDER/tests
MOC_DIR = $$BUILD_FOLDER/tests
RCC_DIR = $$BUILD_FOLDER/tests
UI_DIR = $$BUILD_FOLDER/tests

INCLUDEPATH += ../arm_client/ ../dsp_server

# for testin dsp code on desktop
INCLUDEPATH += /opt/trik-dsp/dsplib_3_1_1_1/packages/

HEADERS += \
    arm_client/recording/wavFileTest.h \
    arm_client/signal/signalTest.h \
    arm_client/signal/sampleTest.h \
    arm_client/recording/recordtest.h \
    tests.h \
    dsp_server/denoise/denoiseTest.h \
    ../dsp_server/trik/iaudenc1_denoise/include/internal/denoise.h

SOURCES += \
    main.cpp \
    arm_client/recording/recordtest.cpp \
    tests.cpp \
    dsp_server/denoise/denoiseTest.cpp \
    ../dsp_server/trik/iaudenc1_denoise/src/denoise.c

# for testing dsp code on desktop
INCLUDEPATH += /opt/trik-dsp/dsplib_3_1_1_1/packages/

HEADERS += /opt/trik-dsp/dsplib_3_1_1_1/packages/ti/dsplib/src/DSPF_sp_lms/c674/DSPF_sp_lms_cn.h \
           /opt/trik-dsp/dsplib_3_1_1_1/packages/ti/dsplib/src/DSPF_sp_w_vec/c674/DSPF_sp_w_vec_cn.h

SOURCES += /opt/trik-dsp/dsplib_3_1_1_1/packages/ti/dsplib/src/DSPF_sp_lms/c674/DSPF_sp_lms_cn.c \
           /opt/trik-dsp/dsplib_3_1_1_1/packages/ti/dsplib/src/DSPF_sp_w_vec/c674/DSPF_sp_w_vec_cn.c

OBJ_PATH = $$BUILD_FOLDER/arm_client
OBJECTS += $$OBJ_PATH/signal.o \
    $$OBJ_PATH/sample.o \
    $$OBJ_PATH/wavFile.o \
    $$OBJ_PATH/soundRecorder.o \
    $$OBJ_PATH/moc_soundRecorder.o
