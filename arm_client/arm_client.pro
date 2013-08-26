#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T14:58:22
#
#-------------------------------------------------

QT       += core
QT -= gui


TARGET = arm_client
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
}

include(signal/signal.pri)
include(recording/recording.pri)

SOURCES +=\
    voiceCommandSensor.cpp \
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
    main.cpp

HEADERS  += define.h \
    buildParam.h \
    voiceCommandSensor.h \
    #testwindow.h \
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

# подключаем pocketsphinx
INCLUDEPATH +=  /usr/local/include/sphinxbase \
    /usr/local/include/pocketsphinx

#  -L/usr/local/lib
LIBS += -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm

OTHER_FILES +=
