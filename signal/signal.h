#ifndef SIGNAL_H
#define SIGNAL_H

#include "buildParam.h"

#include <cmath>
#include <cstring>
#include <QObject>
#include <QtEndian>
#include <QVector>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioFormat>
#else
    #include <QtMultimedia/QAudioFormat>
#endif

#include "define.h"
#include "sample.h"

class Sample;

/**
  * Класс-контейнер для цифрового звукового моно сигнала.
  * Объект хранит информацию об амплитуде звуковой волны.
  *
  * Класс поддерживает данные pcm, записанные с размером сэмпла (sample size) равным 8 или 16 бит.
  */
class Signal
{
public:
    /**
      * Класс исключений, генерируемых при попытке доступа к значению сигнала вне диапозона.
      */
    class OutOfSignalRangeExc {};
    /**
      *
      */
    class SampleSizeUnset {};
    /**
      *
      */
    class SampleRateUnset {};
    /**
      * Создание пустого сигнала.
      */
    Signal();
    /**
      * Создание сигнала длиной n сэмплов, инициализированного нулями.
      *
      * @param format Формат сигнала.
      */
    Signal(int n, const QAudioFormat& signalFormat);
    /**
      * Создание сигнала из массива байт.
      *
      * @param byteArray Массив байт, кодирующих сигнал.
      * @param signalFormat Формат данных, содержащихся в byteArray.
      *     Должен определять размер сэмпла (8/16 бит) и порядок байт для 16-битного сэмпла (little-endian/big-endian)
      */
    Signal(const QByteArray& byteArray, const QAudioFormat& signalFormat);
    /**
      *
      */
    void setData(const QByteArray& byteArray, const QAudioFormat& signalFormat);
    /**
      *
      */
    char* data();
    /**
      *
      */
    const char* data() const;
    /**
      * Возвращает формат сигнала.
      */
    QAudioFormat getFormat() const;
    /**
      * Устанавливает формат сигнала.
      */
    void setFormat(const QAudioFormat& signalFormat);
    /**
      * Оператор возвращает сэмпл в позиции i сигнала.
      */
    Sample operator[](int i) throw(OutOfSignalRangeExc, SampleSizeUnset);
    /**
      * Оператор возвращает сэмпл в позиции i сигнала.
      */
    const Sample operator[](int i) const throw(OutOfSignalRangeExc, SampleSizeUnset);
    /**
      *
      */
    bool operator==(const Signal& signal) const;
    /**
      * Возвращает размер сэмпла в байтах.
      */
    int sampleSize() const throw(SampleSizeUnset);
    /**
      * Возвращает частоту дискретизации.
      */
    int sampleRate() const throw(SampleRateUnset);
    /**
      * Возвращает размер сигнала (кол-во сэмплов).
      */
    int size() const;
    /**
      * Изменяет длину сигнала.
      * Если новая длина больше, увеличивает размер и заполняет новые сэмплы нулями.
      * Иначе удаляет часть сигнала.
      *
      * @param n Новая длина сигнала в сэмплах.
      */
    void resize(int n);
    /**
      *
      */
    int time(int i) const throw(OutOfSignalRangeExc, SampleRateUnset);
    /**
      * Возвращает копию части сигнала.
      *
      * @param start Позиция начала копирования.
      * @param length Длина копируемого сигнала (если -1, то копируются все сэмплы, начиная с позиции start).
      */
    Signal subSignal(int start, int length = -1) const;
private:
    bool sampleSizeSet() const;
    bool sampleRateSet() const;

    QByteArray bytes;
    QAudioFormat format;
};

#endif // SIGNAL_H
