#pragma once

#include <cmath>
#include <cstring>
#include <QObject>
#include <QAudioFormat>

/**
  * Класс-контейнер для цифрового звукового моно сигнала.
  * Объект хранит информацию об амплитуде звуковой волны.
  * Информация о сигнале может храниться в объекте в двух разных формах,
  * как массив байт или как массив переменных double.
  * В первом случае, методы объекта будут сами осуществлять перевод байт в double.
  *
  * Класс поддерживает данные pcm, записанные с размером сэмпла (sample size) равным 8 или 16 бит.
  */
class Signal
{
public:
    /**
      * Класс исключений, генерируемых при попытке доступа к значению сигнала вне диапозона
      */
    class OutOfSignalRangeExc {};
    /**
      * Создание пустого сигнала.
      */
    Signal();
    /**
      * Создание сигнала по массиву байт.
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
    ~Signal();
    /**
      * Оператор возвразает значение амплитуды в позиции i сигнала
      */
    double operator[](unsigned int i) throw(OutOfSignalRangeExc);
    /**
      * Возвращает массив байт, кодирующих сигнал в соответствии с установленным форматом
      */
    QByteArray getBytes();
    /**
      * Возвращает массив значений амплитуды сигнала
      */
    double* getData();
    /**
      * Возвращает массив 8-битных pcm сэмплов (signed), кодирующих данный сигнал.
      * Массив размещается в динамической памяти, после использования её необходимо очистить.
      */
    char* get8bitSamples();
    /**
      * Возвращает массив 16-битных pcm сэмплов (signed, little-endian),
      * кодирующих данный сигнал.
      * Массив размещается в динамической памяти, после использования её необходимо очистить
      */
    short* get16bitSamples();
    QAudioFormat getFormat() const;
    /**
      * Установка формата массива байт.
      * Если объект содержит массив значений амплитуды(или не содержит ничего),
      * то формат будет использован при попытке конвертирования массива double
      * в массив байт (например, при записи сигнала в wav файл).
      * Если объект уже хранит массив байт, то вся информация будет перекодирована в соответсвии
      * с новым форматом.
      */
    void setFormat(QAudioFormat format);
    unsigned int size() const;
    /**
      * Конвертация pcm в double
      *
      * @param pcm конвертируемое значение
      * @param pcmSize размер значения pcm в битах (8 или 16)
      */
    static double pcmToDouble(int pcm, int pcmSize);
    /**
      * Конвертация double в pcm
      *
      * @param pcm конвертируемое значение
      * @param pcmSize размер значения pcm в битах (8 или 16)
      */
    static int doubleToPcm(double val, int pcmSize);
private:

    void doublesToByteArray();
    void byteArrayToDoubles();

    QByteArray bytes;
    QAudioFormat bytesFormat;
    bool bytesSetFlag;
    double* values;
    unsigned int valuesSize;
    bool valuesSetFlag;

    static QByteArray convertByteArray(QByteArray array, QAudioFormat oldFormat, QAudioFormat newFormat);
    static const int PCM8MaxAmplitude = 255;
    static const int PCM16MaxAmplitude = 65535;
};

