#pragma once

#include <cmath>
#include <cstring>
#include <QObject>
#include <QtEndian>
#include <QVector>
#include <QAudioFormat>
#include "sample.h"

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
      * Класс исключений, генерируемых при попытке доступа к значению сигнала вне диапозона.
      */
    class OutOfSignalRangeExc {};
    /**
      * Создание пустого сигнала.
      */
    Signal();
    /**
      * Создание сигнала длиной n сэмплов, инициализированного нулями.
      *
      * @param sampleRate Частота дискретизации сигнала.
      */
    Signal(int n, int sampleRate = 16000);
    Signal(double* array, int arraySize, int sampleRate = 16000);
    Signal(float* array, int size, int sampleRate = 16000);
    Signal(char* array, int arraySize, int sampleRate = 16000);
    Signal(short* array, int arraySize, Sample::ByteOrder byteOrder = Sample::LittleEndian, int sampleRate = 16000);
    Signal(unsigned char* array, int arraySize, int sampleRate = 16000);
    Signal(unsigned short* array, int arraySize, Sample::ByteOrder byteOrder = Sample::LittleEndian, int sampleRate = 16000);
    /**
      * Создание сигнала по массиву байт.
      *
      * @param byteArray Массив байт, кодирующих сигнал.
      * @param signalFormat Формат данных, содержащихся в byteArray.
      *     Должен определять размер сэмпла (8/16 бит) и порядок байт для 16-битного сэмпла (little-endian/big-endian)
      *     тип сэмпла подразумевается знаковый
      */
    Signal(const QByteArray& byteArray, const QAudioFormat& signalFormat);
    /**
      * Возвращает массив значений амплитуды сигнала в виде double (в диапозоне от -1.0 до 1.0).
      */
    double* toDoubleArray() const;
    /**
      * Возвращает массив значений амплитуды сигнала в виде float (в диапозоне от -1.0 до 1.0).
      */
    float* toFloatArray() const;
    /**
      * Возвращает массив 8-битных pcm сэмплов (signed), кодирующих данный сигнал.
      * Массив размещается в динамической памяти, после использования её необходимо очистить.
      */
    char* toPcm8Array() const;
    /**
      * Возвращает массив 16-битных pcm сэмплов (signed), кодирующих данный сигнал.
      * Порядок байт в сэмпле устанавливается методом setByteOrder().
      * Массив размещается в динамической памяти, после использования её необходимо очистить.
      *
      * @param byteOrd порядок байт в сэмплах массива.
      */
    short* toPcm16Array(Sample::ByteOrder byteOrder = Sample::LittleEndian) const;
    /**
      * Возвращает массив 8-битных pcm сэмплов (unsigned), кодирующих данный сигнал.
      * Массив размещается в динамической памяти, после использования её необходимо очистить.
      */
    unsigned char* toUPcm8Array() const;
    /**
      * Возвращает массив 16-битных pcm сэмплов (unsigned), кодирующих данный сигнал.
      * Порядок байт в сэмпле устанавливается методом setByteOrder().
      * Массив размещается в динамической памяти, после использования её необходимо очистить.
      *
      * @param byteOrd порядок байт в сэмплах массива.
      */
    unsigned short* toUPcm16Array(Sample::ByteOrder byteOrder = Sample::LittleEndian) const;
    /**
      * Возвращает массив байт, кодирующих сигнал в соответствии с его форматом.
      */
    QByteArray toByteArray();
    /**
      * Возвращает формат сигнала.
      */
    QAudioFormat getFormat();
    /**
      * Устанавливает формат сигнала.
      */
    void setFormat(const QAudioFormat& signalFormat);
    /**
      * Оператор возвращает сэмпл в позиции i сигнала.
      */
    Sample& operator[](int i) throw(OutOfSignalRangeExc);
    /**
      * Оператор возвращает сэмпл в позиции i сигнала.
      */
    const Sample& operator[](int i) const throw(OutOfSignalRangeExc);
    bool operator==(const Signal& signal) const;
    /**
      * Возвращает размер сигнала (кол-во сэмплов).
      */
    int size() const;
    /**
      * Изменяет длину сигнала.
      * Если новая длина больше, увеличивает размер и заполняет новые сэмплы нулями.
      * Иначе удаляет часть сигнала.
      *
      * @param n Новая длина сигнала.
      */
    void resize(int n);
    /**
      * Возвращает копию части сигнала.
      *
      * @param start Позиция начала копирования.
      * @param length Длина копируемого сигнала (если -1, то копируются все сэмплы, начиная с позиции start).
      */
    Signal subSignal(int start, int length = -1) const;
private:
    Signal(const QVector<Sample>& samplesVector, const QAudioFormat& signalFormat);
    template <typename Type>
    inline void init(Type* array);

    QVector<Sample> samples;
    QAudioFormat format;
};

template <typename Type>
inline void Signal::init(Type* array)
{
    for (int i = 0; i < samples.size(); i++)
        samples[i] = array[i];
}
