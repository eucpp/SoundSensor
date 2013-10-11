#ifndef SAMPLE_H
#define SAMPLE_H

#include <cmath>
#include <QtEndian>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioFormat>
#else
    #include <QtMultimedia/QAudioFormat>
#endif

#include "signal.h"

class Signal;

/**
  * Класс-контейнер для сэмплов звука.
  * Класс хранит указатель на данные объекта Signal и позволяет читать и модифицировать информацию о сэмпле,
  * хранящемся в сигнале.
  * Предоставляет доступ к информации о сэмпле в различных форматах:
  * 8-битный pcm, 16-битный pcm (pcm могут быть только знаковыми),
  * (16 битный pcm может быть записан как в little-endian формате (по умолчанию), так и в big-endian)
  */
class Sample
{
public:
    /**
      * Класс исключений, генерируемых при попытке вызвать оператор присваивания для сэмплов различного размера.
      */
    class DifferentSampleSizes {};
    /**
      * Класс исключений, генерируемых при попытке присвоить значение, выходящее за допустимы диапозон.
      */
    class OutOfRangeValue {};
    /**
      *
      */
    int toInt() const;
    /**
      *
      */
    bool operator==(const Sample& sample) const;
    /**
      *
      */
    bool operator==(int val) const;
    /**
      *
      */
    Sample& operator=(const Sample& sample);
    /**
      *
      */
    Sample& operator=(int val);
    /**
      * Объявляем оператор доступа класса Signal дружественным,
      * чтобы создавать объекты сэмплы с указателями на данные объекта Signal.
      */
    /*
    friend Sample& Signal::operator=(int i) throw(Signal::OutOfSignalRangeExc, Signal::SampleSizeUnset);
    friend const Sample& Signal::operator=(int i) const throw(Signal::OutOfSignalRangeExc, Signal::SampleSizeUnset);
    */
    friend class Signal;
private:
    /**
      * Конструктор - закрытый член класса.
      * Объекты Sample можно создавать только из оператора доступа класса Signal.
      */
    Sample(char* _sampleData, const Signal* const _signal);
    Sample(const char* _constSampleData, const Signal* const _signal);
    /**
      *
      */
    Sample(const Sample& sample);
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

    /**
      *
      */
    char* sampleData;
    /**
      *
      */
    const char* constSampleData;
    /**
      *
      */
    const Signal* const signal;

    /**
      * Максимальные значения амплитуд pcm.
      */
    static const int PCM8MaxAmplitude;
    static const int PCM8MinAmplitude;
    static const int PCM16MaxAmplitude;
    static const int PCM16MinAmplitude;
};

#endif // SAMPLE_H
