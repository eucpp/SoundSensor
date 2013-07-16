#pragma once

#include "buildParam.h"

#include <cmath>
#include <QtEndian>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioFormat>
#else
    #include <QtMultimedia/QAudioFormat>
#endif

#include "define.h"

/**
  * Класс-контейнер для сэмплов звука.
  * Предоставляет доступ к информации о сэмпле в различных форматах:
  * double в диапозоне от -1.0 до 1.0, 8-битный pcm, 16-битный pcm (pcm могут быть как знаковыми, так и беззнаковыми),
  * (16 битный pcm может быть записан как в little-endian формате (по умолчанию), так и в big-endian)
  */
class Sample
{
public:

    enum Type
    {
      Unset,
      PCM8,
      PCM16,
      Float
    };
    /*
    enum ByteOrder
    {
        LittleEndian,
        BigEndian
    };
    */

    /**
      * Конструктор создаёт пустой объект, устанавливает тип сэмпла Unset.
      * Перед использованием объект должен быть проинициализирован одним из set методов.
      */
    Sample();
    /**
      * Инициализация значением float (от -1.0 до 1.0).
      */
    Sample(float f);
    /**
      * Инициализация значением double (от -1.0 до 1.0), которое приводится к float
      */
    Sample(double d);
    /**
      * Инициализация 8-битным знаковым pcm значением.
      */
    Sample(char pcm);
    /**
      * Инициализация 16-битным знаковым pcm значением.
      *
      * @param byteOrd порядок байт аргумента.
      */
    Sample(short pcm, QAudioFormat::Endian byteOrder = QAudioFormat::LittleEndian);
    /**
      * Инициализация 8-битным беззнаковым pcm значением.
      */
    Sample(unsigned char pcm);
    /**
      * Инициализация 16-битным беззнаковым pcm значением.
      *
      * @param byteOrd порядок байт аргумента.
      */
    Sample(unsigned short pcm, QAudioFormat::Endian byteOrder = QAudioFormat::LittleEndian);
    /**
      * Установка значения сэмпла (float от -1.0 до 1.0)
      */
    void setFloat(float value);
    /**
      * Установка значения сэмпла (8-битный знаковый pcm)
      */
    void setPcm8(char pcm);
    /**
      * Установка значения сэмпла (8-битный беззнаковый pcm)
      */
    void setUPcm8(unsigned char pcm);
    /**
      * Установка значения сэмпла (16-битный знаковый pcm).
      */
    void setPcm16(short pcm, QAudioFormat::Endian byteOrder = QAudioFormat::LittleEndian);
    /**
      * Установка значения сэмпла (16-битный беззнаковый pcm).
      */
    void setUPcm16(unsigned short pcm, QAudioFormat::Endian byteOrder = QAudioFormat::LittleEndian);
    /**
      * Возвращает значение сэмпла в виде double.
      */
    double toDouble() const;
    /**
      * Возвращает значение сэмпла в виде float.
      */
    float toFloat() const;
    /**
      * Возвращает значение сэмпла в виде числа с фиксированной запятой.
      */
    fixed_point toFixedPoint() const;
    /**
      * Возвращает значение сэмпла в виде 8-битного знакового pcm.
      */
    char toPcm8() const;
    /**
      * Возвращает значение сэмпла в виде 16-битного знакового pcm.
      *
      * @param byteOrd порядок байт возвращаемого значения.
      */
    short toPcm16(QAudioFormat::Endian byteOrder = QAudioFormat::LittleEndian) const;
    /**
      * Возвращает значение сэмпла в виде 8-битного беззнакового pcm.
      */
    unsigned char toUPcm8() const;
    /**
      * Возвращает значение сэмпла в виде 16-битного беззнакового pcm.
      *
      * @param byteOrd порядок байт возвращаемого значения.
      */
    unsigned short toUPcm16(QAudioFormat::Endian byteOrder = QAudioFormat::LittleEndian) const;
    bool operator==(const Sample& sample) const;
    Sample& operator=(const Sample& sample);
    /**
      * Устанавливает размер хранимого сэмпла.
      * При несовпадении текущего и нового размера метод конвертирует текущее значение.
      */
    //void setSampleSize(PCMSize size);
    /**
      * Возвращает тип сэмпла.
      */
    Type getSampleType() const;
private:
    /**
      * Конвертация pcm в double.
      *
      * @param pcm конвертируемое значение.
      * @param size размер значения pcm в битах (8 или 16).
      */
    static float pcmToFloat(int pcm, int size);
    /**
      * Конвертация double в pcm.
      *
      * @param pcm конвертируемое значение.
      * @param size размер значения pcm в битах (8 или 16).
      */
    static int floatToPcm(float val, int size);

    union
    {
        float floatValue;
        short pcmValue;
    };
    Type type;

    /**
      * Максимальные значения амплитуд в pcm.
      * Используются при конвертации.
      */
    static const int PCM8MaxAmplitude;
    static const int PCM16MaxAmplitude;
    /**
      * Погрешность при сравнении float.
      */
    static const float eps;
};
