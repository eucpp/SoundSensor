#pragma once

#include <cmath>
#include <QtEndian>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioFormat>
#else
    #include <QtMultimedia/QAudioFormat>
#endif

/**
  * Класс-контейнер для сэмплов звука.
  * Предоставляет доступ к информации о сэмпле в различных форматах:
  * double в диапозоне от -1.0 до 1.0, 8-битный pcm, 16-битный pcm (pcm могут быть как знаковыми, так и беззнаковыми),
  * (16 битный pcm может быть записан как в little-endian формате (по умолчанию), так и в big-endian)
  */
class Sample
{
public:
    enum PCMSize
    {
      PCM8,
      PCM16
    };
    enum ByteOrder
    {
        LittleEndian,
        BigEndian
    };

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
      *
      * @param byteOrd порядок байт аргумента.
      */
    Sample(short pcm, ByteOrder byteOrder = LittleEndian);
    /**
      * Инициализация 8-битным беззнаковым pcm значением.
      */
    Sample(unsigned char pcm);
    /**
      * Инициализация 16-битным беззнаковым pcm значением.
      *
      * @param byteOrd порядок байт аргумента.
      */
    Sample(unsigned short pcm, ByteOrder byteOrder = LittleEndian);
    /**
      * Установка значения сэмпла (16-битный знаковый pcm).
      */
    inline void setPcm16(short pcm, ByteOrder byteOrder = LittleEndian);
    /**
      * Установка значения сэмпла (16-битный беззнаковый pcm).
      */
    inline void setUPcm16(unsigned short pcm, ByteOrder byteOrder = LittleEndian);
    /**
      * Возвращает значение сэмпла в виде double.
      */
    double toDouble() const;
    /**
      * Возвращает значение сэмпла в виде float.
      */
    float toFloat() const;
    /**
      * Возвращает значение сэмпла в виде 8-битного знакового pcm.
      */
    char toPcm8() const;
    /**
      * Возвращает значение сэмпла в виде 16-битного знакового pcm.
      *
      * @param byteOrd порядок байт возвращаемого значения.
      */
    short toPcm16(ByteOrder byteOrder = LittleEndian) const;
    /**
      * Возвращает значение сэмпла в виде 8-битного беззнакового pcm.
      */
    unsigned char toUPcm8() const;
    /**
      * Возвращает значение сэмпла в виде 16-битного беззнакового pcm.
      *
      * @param byteOrd порядок байт возвращаемого значения.
      */
    unsigned short toUPcm16(ByteOrder byteOrder = LittleEndian) const;
    bool operator==(const Sample& sample) const;
    /**
      * Устанавливает размер хранимого сэмпла.
      * При несовпадении текущего и нового размера метод конвертирует текущее значение.
      */
    void setSampleSize(PCMSize size);
    /**
      * Возвращает размер сэмпла.
      */
    PCMSize getSampleSize();
private:
    /**
      * Конвертация pcm в double.
      *
      * @param pcm конвертируемое значение.
      * @param size размер значения pcm в битах (8 или 16).
      */
    static double pcmToDouble(int pcm, PCMSize size);
    /**
      * Конвертация double в pcm.
      *
      * @param pcm конвертируемое значение.
      * @param size размер значения pcm в битах (8 или 16).
      */
    static int doubleToPcm(double val, PCMSize size);

    short value;
    PCMSize pcmSize;

    /**
      * Максимальные значения амплитуд в pcm.
      * Используются при конвертации.
      */
    static const int PCM8MaxAmplitude = 127;
    static const int PCM16MaxAmplitude = 32767;
};

inline void Sample::setPcm16(short pcm, ByteOrder byteOrder)
{
    pcmSize = PCM16;
    if (byteOrder == LittleEndian)
        value = qFromLittleEndian(pcm);
    else
        value = qFromBigEndian(pcm);
}
inline void Sample::setUPcm16(unsigned short pcm, ByteOrder byteOrder)
{
    pcmSize = PCM16;
    if (byteOrder == LittleEndian)
        value = qFromLittleEndian(pcm - PCM16MaxAmplitude - 1);
    else
        value = qFromBigEndian(pcm - PCM16MaxAmplitude - 1);
}
