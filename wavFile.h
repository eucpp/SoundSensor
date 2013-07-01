#pragma once

#include <iostream>
#include <cstring>
#include <QObject>
#include <QAudioFormat>
#include <QFile>
#include "signal.h"
#include "soundRecorder.h"

/**
  * Класс для работы с wav файлами.
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
        NotOpen
    };

    /**
      * Конструктор по умолчанию.
      * Если используется, то перед дальнейшим использованием необходимо передать объекту имя файла.
      */
    WavFile();
    /**
      * @param filename Имя файла.
      */
    WavFile(const QString& filename);
    /**
      * Открытие файла.
      * Если файл открыт в режиме WriteOnly, то перед записью данных в файл
      * необходимо установить заголовок файла методом setHeader().
      * При открытии в других режимах, будет использоваться имеющийся заголовок файла.
      *
      * @param mode Режим работы с файлом.
      */
    void open(OpenModes mode);
    /**
      * Открытие файла.
      *
      * @param mode Режим работы с файлом.
      * @param format Формат файла. Если файл открыт в режиме WriteOnly этот параметр будет
      *     использован для записи заголовка файла. Все данные, которые будут в дальнейшем
      *     передаваться методу write() будут записывать данные в этом формате.
      *     Если файл открыт в режиме Read/Append, этот параметр игнорируется.
      *     Заголовок должен устанавливать размер сэмпла, частоту дискретизации и кол-во каналов (моно/стерео).
      *     Если размер сэмплов - 8бит, то тип сэмплов - беззнаковый, иначе знаковый.
      */
    void open(OpenModes mode, const QAudioFormat& format);
    /**
      * Закрытие файла.
      * Закрытие файла происходит автоматически при уничтожении объекта.
      */
    void close();
    /**
      * Устанавливает имя файла.
      * Если на момент вызова метода открыт другой файл, то он будет закрыт, а объект будет привязан к новому файлу.
      */
    void setFileName(const QString& filename);
    /**
      * Имя текущего файла.
      */
    QString fileName() const;
    /**
      * Проверяет, установлен ли заголовок.
      */
    bool headerSet() const;
    /**
      * Устанавливает заголовок.
      * Если файл открыт в режиме WriteOnly и до вызова метода какие-то данные уже были записаны,
      * и новый заголовок отличается от старого, то
      * метод перекодирует содержимое файла в соответствии с новым форматом.
      *
      * @param format Новый заголовок.
      * @throw WriteDisabledExc Если файл открыт в режиме ReadOnly/Append, модификация заголовка запрещена.
      */
    void setHeader(const QAudioFormat& format) throw(WriteDisabledExc);
    /**
      * Возвращает текущий заголовок wav файла.
      * Если заголовок не был установлен, возвращает объект QAudioFormat, создаваемый конструктором по умолчанию.
      */
    QAudioFormat getHeader() const;
    bool isOpen() const;
    /**
      * Переходит к позиции pos в файле (отсчёт в сэмплах).
      */
    bool seek(int pos);
    /**
      * Возвращает текущую позицию чтения/записи в файле (отсчёт в сэмплах).
      */
    int pos();
    /**
      * Возвращает размер данных в сэмплах.
      * (размер файла минус 44 байта(размер заголовка) делить на размер сэмпла).
      * Если файл не был открыт возвращает 0.
      */
    int size();
    /**
      * Читает данные из wav файла в сигнал.
      *
      * @param length Кол-во сэмплов для чтения.
      * @return Объект-сигнал, либо пустой сигнал, если файл не был открыт.
      */
    Signal read(int length) throw(ReadDisabledExc);
    /**
      * Читает содержимое всего файла в сигнал.
      *
      * @return Объект-сигнал, либо пустой сигнал, если файл не был открыт.
      */
    Signal readAll() throw(ReadDisabledExc);
    /**
      * Записывает в wav файл сигнал.
      * Если файл открыт только на чтение, бросается исключение WriteDisabledExc.
      * Если файл не был открыт, либо если не был установлен заголовок, запись не совершается.
      *
      * @param signal Сигнал для записи.
      * @param length Кол-во сэмплов, которые будут записаны. Если передано значение -1 (по умолчанию), то
      *     будет записан весь сигнал.
      * @return Кол-во сэмплов, реально записанных в файл (либо 0, если файл не был открыт).
      * @throw WriteDisabledExc Если файл открыт только на чтение.
      */
    int write(Signal signal, int length = -1) throw(WriteDisabledExc);
private:
    /**
      * Класс исключений, генерируемых при чтении заголовка (если заголовок оказался некорректным).
      */
    class UncorrectHeader {};
    /**
      * Структура заголовка wav файла.
      */
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
      */
    void writeHeader(const QAudioFormat& format);
    void setDataSize(int size);
    bool isCorrectFormat(const QAudioFormat& format);

    QFile file;
    OpenModes openmode;
    QAudioFormat header;
    bool headerSetFlag;
};


