#pragma once

#include <math.h>
#include <QObject>
#include <QAudioFormat>

/**
  * Класс-контейнер для цифрового звукового сигнала.
  * Объект хранит информацию об амплитуде звуковой волны.
  * Информация о сигнале может храниться в объекте в двух разных формах,
  * как массив байт или как массив переменных double.
  * В первом случае, методы объекта будут сами осуществлять перевод байт в double.
  */
class Signal
{
public:
    /**
      * Создание сигнала по массиву байт
      *
      * @param byteArray Массив байт, кодирующих сигнал
      * @param signalFormat Формат данных, содержащихся в byteArray
      */
    Signal(QByteArray byteArray, QAudioFormat signalFormat);
    /**
      * Создание сигнала по массиву значений (амплитуды волны)
      *
      * @param vals Массив значений
      */
    Signal(double* vals, unsigned int valsSize);
    /**
      * Оператор возвразает значение амплитуды в позиции i сигнала
      */
    double operator[](unsigned int i);
    /**
      * Возвращает массив байт, кодирующих сигнал в соответствии с установленным форматом
      */
    QByteArray getBytes();
    /**
      * Возвращает массив значений амплитуды сигнала
      */
    QAudioFormat getFormat();
    unsigned int getSize();
    double* getData();
    static double pcmToDouble(int pcm);
    static int doubleToPcm(double val);
private:
    QByteArray doublesToByteArray();
    double* byteArrayToDoubles();
    QByteArray bytes;
    bool bytesSetFlag;
    QAudioFormat bytesFormat;
    double* values;
    unsigned int size;

    static const int PCM4MaxAmplitude = 128;
};

