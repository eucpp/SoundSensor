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
    QRealFourier/code/sources/qwindowfunction.cpp \
    QRealFourier/code/sources/qfouriervariablecalculator.cpp \
    QRealFourier/code/sources/qfouriertransformer.cpp \
    QRealFourier/code/sources/qfourierfixedcalculator.cpp \
    QRealFourier/code/sources/qfouriercalculator.cpp \
    QRealFourier/code/sources/qcomplexnumber.cpp \
    spectrumAnalyzer.cpp \
    spectrogram.cpp \
    utils.cpp

HEADERS  += testwindow.h \
    soundRecorder.h \
    QRealFourier/code/headers/qwindowfunction.h \
    QRealFourier/code/headers/qfouriervariablecalculator.h \
    QRealFourier/code/headers/qfouriertransformer.h \
    QRealFourier/code/headers/qfourierfixedcalculator.h \
    QRealFourier/code/headers/qfouriercalculator.h \
    QRealFourier/code/headers/qcomplexnumber.h \
    QRealFourier/code/fftreal/OscSinCos.hpp \
    QRealFourier/code/fftreal/OscSinCos.h \
    QRealFourier/code/fftreal/FFTRealUseTrigo.hpp \
    QRealFourier/code/fftreal/FFTRealUseTrigo.h \
    QRealFourier/code/fftreal/FFTRealSelect.hpp \
    QRealFourier/code/fftreal/FFTRealSelect.h \
    QRealFourier/code/fftreal/FFTRealPassInverse.hpp \
    QRealFourier/code/fftreal/FFTRealPassInverse.h \
    QRealFourier/code/fftreal/FFTRealPassDirect.hpp \
    QRealFourier/code/fftreal/FFTRealPassDirect.h \
    QRealFourier/code/fftreal/FFTRealFixLenParam.h \
    QRealFourier/code/fftreal/FFTRealFixLen.hpp \
    QRealFourier/code/fftreal/FFTRealFixLen.h \
    QRealFourier/code/fftreal/FFTReal.hpp \
    QRealFourier/code/fftreal/FFTReal.h \
    QRealFourier/code/fftreal/DynArray.hpp \
    QRealFourier/code/fftreal/DynArray.h \
    QRealFourier/code/fftreal/def.h \
    QRealFourier/code/fftreal/Array.hpp \
    QRealFourier/code/fftreal/Array.h \
    spectrumAnalyzer.h \
    spectrogram.h \
    utils.h

FORMS    += testwindow.ui \

INCLUDEPATH += /usr/include/QtMultimediaKit
INCLUDEPATH += /usr/include/QtMobility
