#-------------------------------------------------
#
# Project created by QtCreator 2013-03-24T14:58:22
#
#-------------------------------------------------

QT       += core testlib
QT -= gui


TARGET = SoundSensor
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

SOURCES += main.cpp\
#        testwindow.cpp \
    soundRecorder.cpp \
    Alglib/fasttransforms.cpp \
    Alglib/ap.cpp \
    Alglib/alglibmisc.cpp \
    Alglib/alglibinternal.cpp \
    signal.cpp \
    wavFile.cpp \
    voiceCommandSensor.cpp \
    sample.cpp \
    tests/recordtest.cpp \
    tests/signaldetector.cpp \
    alglibCorrelator.cpp \
    simpleCorrelator.cpp

HEADERS  += soundRecorder.h \
    #testwindow.h \
    Alglib/fasttransforms.h \
    Alglib/ap.h \
    Alglib/alglibinternal.h \
    Alglib/alglibmisc.h \
    signal.h \
    wavFile.h \
    tests/signalTest.h \
    voiceCommandSensor.h \
    tests/wavFileTest.h \
    sample.h \
    tests/sampleTest.h \
    tests/recordtest.h \
    buildParam.h \
    tests/correlatorTest.h \
    tests/signaldetector.h \
    alglibCorrelator.h \
    correlator.h \
    simpleCorrelator.h \
    spectrum.h \
    fftreal/ffft/OscSinCos.hpp \
    fftreal/ffft/OscSinCos.h \
    fftreal/ffft/FFTRealUseTrigo.hpp \
    fftreal/ffft/FFTRealUseTrigo.h \
    fftreal/ffft/FFTRealSelect.hpp \
    fftreal/ffft/FFTRealSelect.h \
    fftreal/ffft/FFTRealPassInverse.hpp \
    fftreal/ffft/FFTRealPassInverse.h \
    fftreal/ffft/FFTRealPassDirect.hpp \
    fftreal/ffft/FFTRealPassDirect.h \
    fftreal/ffft/FFTRealFixLenParam.h \
    fftreal/ffft/FFTRealFixLen.hpp \
    fftreal/ffft/FFTRealFixLen.h \
    fftreal/ffft/FFTReal.hpp \
    fftreal/ffft/FFTReal.h \
    fftreal/ffft/DynArray.hpp \
    fftreal/ffft/DynArray.h \
    fftreal/ffft/def.h \
    fftreal/ffft/Array.hpp \
    fftreal/ffft/Array.h \
    spectrumElement.h \
    fourierTransform.h \
    fftrealWrap.h \
    tests/fourierTransformTest.h

#FORMS    += testwindow.ui \

# подключаем pocketsphinx
INCLUDEPATH +=  /usr/local/include/sphinxbase \
    /usr/local/include/pocketsphinx

#  -L/usr/local/lib
LIBS+= -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm
