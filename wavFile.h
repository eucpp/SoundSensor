#pragma once

#include <iostream>
#include <QObject>
#include <QAudioFormat>
#include <QFile>
#include "signal.h"
#include "soundRecorder.h"

/**
  * Класс для работы с wav файлами
  */
class WavFile
{
public:
    /**
      * Класс исключений, бросаемых в случае, если не удалось открыть файл
      */
    class OpenFileExc {};
    /**
      * Класс исключений, бросаемых при попытке записи в файл,
      * открытый только для чтения.
      */
    class WriteDisabledExc {};
    /**
      * Класс исключений, бросаемых при попытке чтения из файла,
      * открытого только для записи.
      */
    class ReadDisabledExc {};
    /**
      * Содержит режимы работы с файлом.
      */
    enum OpenModes
    {
        ReadOnly,
        WriteOnly,
        Append,
        ReadWrite,
        NotOpen
    };

    /**
      * @param filename Имя файла.
      */
    WavFile(const QString& filename);
    /**
      * Открытие файла.
      * Если файл открыт в режиме WriteOnly для записи заголовка будет использован
      * формат по умолчанию ( = SoundRecorder::defaultAudioFormat())
      *
      * @param mode Режим работы с файлом.
      * @return Возвращает формат, соответствующий заголовку wav файла.
      *     Если файл был открыт в режиме WriteOnly,
      *     возвращаемое значение совпадает c форматом по умолчанию.
      */
    QAudioFormat open(OpenModes mode);
    /**
      * Открытие файла.
      *
      * @param mode Режим работы с файлом.
      * @param format Формат файла. Если файл открыт в режиме WriteOnly этот параметр будет
      *     использован для записи заголовка файла. Все данные, которые будут в дальнейшем
      *     передаваться методу write() будут записывать данные в этом формате.
      *     Если файл открыт в каком-либо другом режиме, этот параметр игнорируется, и запись
      *     производится в соответствии с имеющимся заголовком.
      * @return Возвращает формат, соответствующий заголовку wav файла.
      *     Если файл был открыт в режиме WriteOnly, возвращаемое значение совпадает с параметром format
      */
    QAudioFormat open(OpenModes mode,
                      const QAudioFormat& format);
    /**
      * Закрытие файла
      */
    void close();
    bool isOpen() const;
    bool seek(unsigned int pos);
    /**
      * Возвращает текущую позицию чтения/записи в файле.
      */
    unsigned int pos();
    /**
      * Читает всё содержимое файла в объект-сигнал.
      * Если файл открыт только на запись или на дозапись, бросается исключение ReadDisabledExc.
      */
    Signal readSignal() throw(ReadDisabledExc);
    /**
      * Записывает в wav файл сигнал.
      * Если файл открыт только на чтение, бросается исключение WriteDisabledExc.
      */
    void writeSignal(Signal signal) throw(WriteDisabledExc);
    /**
      * Возвращает размер данных в байтах.
      * (размер файла минус 44 байта(размер заголовка)).
      * Если файл не был открыт, либо был открыт в режиме WriteOnly или Append,
      * возвращает 0.
      */
    unsigned int dataSize();
private:
    struct Header
    {
        // WAV-формат начинается с RIFF-заголовка:

            // Содержит символы "RIFF" в ASCII кодировке
            // (0x52494646 в big-endian представлении)
            char chunkId[4];

            // 36 + subchunk2Size, или более точно:
            // 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
            // Это оставшийся размер цепочки, начиная с этой позиции.
            // Иначе говоря, это размер файла - 8, то есть,
            // исключены поля chunkId и chunkSize.
            unsigned int chunkSize;

            // Содержит символы "WAVE"
            // (0x57415645 в big-endian представлении)
            char format[4];

            // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
            // Подцепочка "fmt " описывает формат звуковых данных:

            // Содержит символы "fmt "
            // (0x666d7420 в big-endian представлении)
            char subchunk1Id[4];

            // 16 для формата PCM.
            // Это оставшийся размер подцепочки, начиная с этой позиции.
            unsigned int subchunk1Size;

            // Аудио формат, полный список можно получить здесь http://audiocoding.ru/wav_formats.txt
            // Для PCM = 1 (то есть, Линейное квантование).
            // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
            unsigned short audioFormat;

            // Количество каналов. Моно = 1, Стерео = 2 и т.д.
            unsigned short numChannels;

            // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
            unsigned int sampleRate;

            // sampleRate * numChannels * bitsPerSample/8
            unsigned int byteRate;

            // numChannels * bitsPerSample/8
            // Количество байт для одного сэмпла, включая все каналы.
            unsigned short blockAlign;

            // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
            unsigned short bitsPerSample;

            // Подцепочка "data" содержит аудио-данные и их размер.

            // Содержит символы "data"
            // (0x64617461 в big-endian представлении)
            char subchunk2Id[4];

            // numSamples * numChannels * bitsPerSample/8
            // Количество байт в области данных.
            unsigned long subchunk2Size;

            // Далее следуют непосредственно Wav данные.
    };

    /**
      * Читает заголовок wav файла
      */
    QAudioFormat readHeader();
    /**
      * Записывает заголовок wav файла.
      *
      * @param format Формат записи
      * @param dataSize размер записываемых в файл данных (без заголовка)
      */
    void writeHeader(const QAudioFormat& format);
    void setDataSize(unsigned int size);
    unsigned int readDataSize();

    QFile file;
    OpenModes openmode;
    QAudioFormat header;
    /**
      * Хранит размер области данных wav файла.
      */
    unsigned int dSize;
};


