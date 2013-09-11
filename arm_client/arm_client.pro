#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T14:58:22
#
#-------------------------------------------------

# тут определяем некоторые переменные и "конфиги" для сборки проекта.

# сборка проекта для тестирования на обычной машине - desktop, сборка для трика - trik
CONFIG += desktop

# общие настройки qt проекта
QT       += core
QT -= gui
TARGET = arm_client
TEMPLATE = app
CONFIG +=  console
CONFIG -= app_bundle

# настройки проекта

# подключаем pocketsphinx
INCLUDEPATH +=  /usr/local/include/sphinxbase \
    /usr/local/include/pocketsphinx

#  -L/usr/local/lib
LIBS += -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm


# специфичные настройки для сборки под трик/десктоп
trik {
    message("Building for Trik")

    QT += multimedia

    DESTDIR = ../trik-build-bin
    OBJECTS_DIR = ../trik-build-bin
    MOC_DIR = ../trik-build-bin

    # подключаем codec engine wrap модуль
    include(codecEngineWrap/codecEngineWrap.pri)

    # подключаем модули для dsp
    INCLUDEPATH += $$CE_INSTALL_DIR/packages $$XDC_INSTALL_DIR/packages $$XDAIS_INSTALL_DIR/packages

    LIBS += -lpthread -lrt -ldl

    # путь к XDAIS
    XDAIS_INSTALL_DIR = /opt/trik-dsp/xdais_7_23_00_06
    # путь к codec_engine
    CE_INSTALL_DIR = /opt/trik-dsp/codec_engine_3_23_00_07
    # путь к xdc
    XDC_INSTALL_DIR = /opt/trik-dsp/xdctools_3_24_07_73
    # путь к osal
    OSAL_INSTALL_DIR = /opt/trik-dsp/osal_1_23_00_04/

    # дальше какое-то колдунство
    #CGTOOLS_V5T ?= __your_CGTOOLS_V5T__
    #CC_V5T ?= __your_CC_V5T__
    CC = $(CGTOOLS_V5T)/$(CC_V5T)

    CFLAGS = "-fPIC -Wall -fno-strict-aliasing $(CCPROFILE.$(PROFILE)) \
        -I. -I./include $(addprefix -I,$(REPO_PATH))"

    CROSS_COMPILE = $(subst -gcc,-,$(CGTOOLS_V5T)/$(CC_V5T))



    QMAKE_CXXFLAGS = "-Dxdc_target_name__=GCArmv5T -Dxdc_target_types__=gnu/targets/arm/std.h"

    # make osal
    QMAKE_EXTRA_TARGETS += osal_debug \
                           cstubs_debug \
                           osal_release \
                           cstubs_release

    osal_debug.target = osal/debug/lib/osal.a
    osal_debug.commands = $(MAKE) -C osal/debug \
                          -f $(OSAL_INSTALL_DIR)/packages/linuxdist/build/Makefile \
                          OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
                          CROSS_COMPILE=$(CROSS_COMPILE) \
                          PRECONFIG=$(OSAL_INSTALL_DIR)/packages/linuxdist/preconfig/development \
                          CFLAGS=-g

    cstubs_debug.target = osal/debug/lib/cstubs.a
    cstubs_debug.commands = $(MAKE) -C osal/debug \
                            -f $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs/Makefile \
                            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
                            CROSS_COMPILE=$(CROSS_COMPILE) \
                            CFLAGS=-g

    osal_release.target = osal/release/lib/osal.a
    osal_release.commands = $(MAKE) -C osal/release \
                            -f $(OSAL_INSTALL_DIR)/packages/linuxdist/build/Makefile \
                            OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
                            CROSS_COMPILE=$(CROSS_COMPILE) \
                            PRECONFIG=$(OSAL_INSTALL_DIR)/packages/linuxdist/preconfig/production \
                            CFLAGS=-O2

    cstubs_release.target = osal/release/lib/cstubs.a
    cstubs_release.commands = $(MAKE) -C osal/release \
                              -f $(OSAL_INSTALL_DIR)/packages/linuxdist/cstubs/Makefile \
                              OSAL_INSTALL_DIR=$(OSAL_INSTALL_DIR) \
                              CROSS_COMPILE=$(CROSS_COMPILE) \
                              CFLAGS=-O2
}
desktop {
    message("Building for desktop")

    CONFIG += mobility
    MOBILITY = multimedia
    INCLUDEPATH += /usr/include/QtMultimediaKit
    INCLUDEPATH += /usr/include/QtMobility

    DEFINES += DESKTOP
}

# подключаем подпроекты
include(signal/signal.pri)
include(recording/recording.pri)



SOURCES += main.cpp \
    voiceCommandSensor.cpp \

HEADERS  += define.h \
    buildParam.h \
    voiceCommandSensor.h \




# тут закоменченный код, пока не удалять

#        testwindow.cpp \
#    Alglib/fasttransforms.cpp \
#    Alglib/ap.cpp \
#    Alglib/alglibmisc.cpp \
#    Alglib/alglibinternal.cpp \
#    tests/signaldetector.cpp \
#    fixed_point/fixed_func.cpp \
#    tests/fourierTransformTest.cpp \
#    signal/correlation/simpleCorrelator.cpp \
#    signal/correlation/fftCorrelator.cpp \
#    signal/fourierTransform/spectrum.cpp \
#    signal/fourierTransform/hannWindow.cpp \
#    signal/fourierTransform/fftrealWrap.cpp \
#    signal/correlation/alglibCorrelator.cpp \
#    motorFilterTest.cpp

#    testwindow.h \
#    Alglib/fasttransforms.h \
#    Alglib/ap.h \
#    Alglib/alglibinternal.h \
#    Alglib/alglibmisc.h \
#    tests/fourierTransformTest.h \
#    tests/correlatorsTimeTest.h \
#    fixed_point/stdint.h \
#    fixed_point/fixsintab.h \
#    fixed_point/fixed_func.h \
#    fixed_point/fixed_class.h \
#    fpml/fixed_point.h \
#    signal/correlation/simpleCorrelator.h \
#    signal/correlation/fftCorrelator.h \
#    signal/correlation/correlator.h \
#    signal/correlation/alglibCorrelator.h \
#    signal/fourierTransform/fftreal/ffft/OscSinCos.hpp \
#    signal/fourierTransform/fftreal/ffft/OscSinCos.h \
#    signal/fourierTransform/fftreal/ffft/FFTRealUseTrigo.hpp \
#    signal/fourierTransform/fftreal/ffft/FFTRealUseTrigo.h \
#    signal/fourierTransform/fftreal/ffft/FFTRealSelect.hpp \
#    signal/fourierTransform/fftreal/ffft/FFTRealSelect.h \
#    signal/fourierTransform/fftreal/ffft/FFTRealPassInverse.hpp \
#    signal/fourierTransform/fftreal/ffft/FFTRealPassInverse.h \
#    signal/fourierTransform/fftreal/ffft/FFTRealPassDirect.hpp \
#    signal/fourierTransform/fftreal/ffft/FFTRealPassDirect.h \
#    signal/fourierTransform/fftreal/ffft/FFTRealFixLenParam.h \
#    signal/fourierTransform/fftreal/ffft/FFTRealFixLen.hpp \
#    signal/fourierTransform/fftreal/ffft/FFTRealFixLen.h \
#    signal/fourierTransform/fftreal/ffft/FFTReal.hpp \
#    signal/fourierTransform/fftreal/ffft/FFTReal.h \
#    signal/fourierTransform/fftreal/ffft/DynArray.hpp \
#    signal/fourierTransform/fftreal/ffft/DynArray.h \
#    signal/fourierTransform/fftreal/ffft/def.h \
#    signal/fourierTransform/fftreal/ffft/Array.hpp \
#    signal/fourierTransform/fftreal/ffft/Array.h \
#    signal/fourierTransform/windowFunction.h \
#    signal/fourierTransform/spectrumElement.h \
#    signal/fourierTransform/spectrum.h \
#    signal/fourierTransform/hannWindow.h \
#    signal/fourierTransform/fourierTransform.h \
#    signal/fourierTransform/fftrealWrap.h \
#    motorFilterTest.h

#FORMS    += testwindow.ui \
