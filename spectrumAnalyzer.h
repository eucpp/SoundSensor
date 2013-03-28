#pragma once

#include <math.h>
#include <QObject>
#include <QByteArray>
#include <QAudioFormat>
#include "QRealFourier/code/headers/qfouriertransformer.h"
#include "spectrogram.h"
#include "utils.h"

class SpectrumAnalyzer : public QObject
{
    Q_OBJECT
public:
    SpectrumAnalyzer(int dataSizeLog, QAudioFormat& audioFormat);
    ~SpectrumAnalyzer();
public slots:
    void calclulateSpectrum(QByteArray byteArray);
signals:
    void spectrumCalculated(Spectrogram);
private:
    QFourierTransformer* fourierTransformer;
    QAudioFormat format;
    int analyzedDataSize;
};

