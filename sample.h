#pragma once

#include <cmath>
#include <QtEndian>

/**
  * Класс-контейнер для сэмплов звука.
  * Предоставляет доступ к информации о сэмпле в различных форматах:
  * double в диапозоне от -1.0 до 1.0, 8-битный pcm, 16-битный pcm (pcm могут быть как знаковыми, так и беззнаковыми),
  * (16 битный pcm может быть записан как в little-endian формате (по умолчанию), так и в big-endian)
  */
class Sample
{
public:
    /**
      * Конструктор инициализирует объект нулевым значением.
      */
    Sample();
    /**
      * Инициализация значением double (от -1.0 до 1.0).
      */
    Sample(double d);
    /**
      * Инициализация 8-битным знаковым pcm значением.
      */
    Sample(char pcm);
    /**
      * Инициализация 16-битным знаковым pcm значением.
      */
    Sample(short pcm);
    /**
      * Инициализация 8-битным беззнаковым pcm значением.
      */
    Sample(unsigned char pcm);
    /**
      * Инициализация 16-битным беззнаковым pcm значением.
      */
    Sample(unsigned short pcm);
    /**
      * Возвращает значение сэмпла в виде double.
      */
    double toDouble();
    /**
      * Возвращает значение сэмпла в виде float.
      */
    float toFloat();
    /**
      * Возвращает значение сэмпла в виде 8-битного знакового pcm.
      */
    char toPcm8();
    /**
      * Возвращает значение сэмпла в виде 16-битного знакового pcm.
      */
    short toPcm16();
    /**
      * Возвращает значение сэмпла в виде 8-битного беззнакового pcm.
      */
    unsigned char toUPcm8();
    /**
      * Возвращает значение сэмпла в виде 16-битного беззнакового pcm.
      */
    unsigned short toUPcm16();

    enum ByteOrder
    {
        LittleEndian,
        BigEndian
    };
    /**
      * Устанавливает порядок байт, используемый при конвертировании в 16-битный pcm.
      */
    void setByteOrder(ByteOrder order);
    /**
      * Возвращает используемый в данный момент порядок байт для записи 16-битных pcm.
      */
    ByteOrder byteOrder();
private:
    /**
      * Конвертация pcm в double.
      *
      * @param pcm конвертируемое значение.
      * @param pcmSize размер значения pcm в битах (8 или 16).
      */
    static double pcmToDouble(int pcm, int pcmSize);
    /**
      * Конвертация double в pcm.
      *
      * @param pcm конвертируемое значение.
      * @param pcmSize размер значения pcm в битах (8 или 16).
      */
    static int doubleToPcm(double val, int pcmSize);

    double value;
    ByteOrder byteOrd;

    /**
      * Максимальные значения амплитуд в pcm.
      * Используются при конвертации.
      */
    static const int PCM8MaxAmplitude = 127;
    static const int PCM16MaxAmplitude = 32767;
};
