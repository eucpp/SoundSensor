#pragma once

#include <iostream>
#include <math.h>
#include <QObject>
#include <QByteArray>
#include <QAudioFormat>
#include "QRealFourier/code/headers/qfouriertransformer.h"
#include "spectrogram.h"
#include "utils.h"

#include "stdlib.h"
#include <QtGlobal>

/**
  * Анализатор спектра.
  * Класс содержит слот calculateSpectrum(), который получает на вход массив байт,
  * выполняет над ним преобразование Фурье и генерирует сигнал spectrumCalculated().
  * Формат входных значений, принимаемых calculateSpectrum(),
  * (таких как длина обрабатываемого фрейма, частота дискретизации и.т.д) передаётся в конструктор
  * во время создания объекта.
  * Для выполнения преобразования Фурье используются библиотеки QRealFourier & FFTReal
  */
class SpectrumAnalyzer : public QObject
{
    Q_OBJECT
public:
    /**
      * Конструктор анализатора спектра.
      *
      * @param dataSizeExp Размер обрабатываемого фрейма - степень двойки.
      *                    Например, если передано 10, то размер будет 2^10 = 1024 байт
      * @param audioFormat Формат передаваемых данных
      */
    SpectrumAnalyzer(int dataSizeExp, QAudioFormat audioFormat);
    ~SpectrumAnalyzer();
public slots:
    /**
      * Вычисление спектра.
      * После окончания работы генерирует сигнал spectrumCalculated()
      */
    void calclulateSpectrum(QByteArray byteArray);
signals:
    /**
      * Сигнал, генерируемый после создания спектрограммы.
      * Содержит объект класса Spectrogram, в котором хранятся данные о спектре.
      */
    void spectrumCalculated(Spectrogram);
private:
    QFourierTransformer* fourierTransformer;
    QAudioFormat format;
    int analyzedDataSize;
};

