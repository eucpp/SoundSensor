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
#    QRealFourier/code/sources/qwindowfunction.cpp \
#    QRealFourier/code/sources/qfouriervariablecalculator.cpp \
#    QRealFourier/code/sources/qfouriertransformer.cpp \
#    QRealFourier/code/sources/qfourierfixedcalculator.cpp \
#    QRealFourier/code/sources/qfouriercalculator.cpp \
#    QRealFourier/code/sources/qcomplexnumber.cpp \
#    spectrumAnalyzer.cpp \
#    spectrogram.cpp \
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
    #QRealFourier/code/headers/qwindowfunction.h \
    #QRealFourier/code/headers/qfouriervariablecalculator.h \
    #QRealFourier/code/headers/qfouriertransformer.h \
    #QRealFourier/code/headers/qfourierfixedcalculator.h \
    #QRealFourier/code/headers/qfouriercalculator.h \
    #QRealFourier/code/headers/qcomplexnumber.h \
    #QRealFourier/code/fftreal/OscSinCos.hpp \
    #QRealFourier/code/fftreal/OscSinCos.h \
    #QRealFourier/code/fftreal/FFTRealUseTrigo.hpp \
    #QRealFourier/code/fftreal/FFTRealUseTrigo.h \
    #QRealFourier/code/fftreal/FFTRealSelect.hpp \
    #QRealFourier/code/fftreal/FFTRealSelect.h \
    #QRealFourier/code/fftreal/FFTRealPassInverse.hpp \
    #QRealFourier/code/fftreal/FFTRealPassInverse.h \
    #QRealFourier/code/fftreal/FFTRealPassDirect.hpp \
    #QRealFourier/code/fftreal/FFTRealPassDirect.h \
    #QRealFourier/code/fftreal/FFTRealFixLenParam.h \
    #QRealFourier/code/fftreal/FFTRealFixLen.hpp \
    #QRealFourier/code/fftreal/FFTRealFixLen.h \
    #QRealFourier/code/fftreal/FFTReal.hpp \
    #QRealFourier/code/fftreal/FFTReal.h \
    #QRealFourier/code/fftreal/DynArray.hpp \
    #QRealFourier/code/fftreal/DynArray.h \
    #QRealFourier/code/fftreal/def.h \
    #QRealFourier/code/fftreal/Array.hpp \
    #QRealFourier/code/fftreal/Array.h \
    #spectrumAnalyzer.h \
    #spectrogram.h \
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
    simpleCorrelator.h

#FORMS    += testwindow.ui \

# подключаем pocketsphinx
INCLUDEPATH +=  /usr/local/include/sphinxbase \
    /usr/local/include/pocketsphinx

#  -L/usr/local/lib
LIBS+= -lpocketsphinx -lsphinxbase -lsphinxad -lpthread -lm
