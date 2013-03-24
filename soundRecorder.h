#pragma once

#include <iostream>
#include <QObject>
#include <QtMultimediaKit/QAudioInput>
#include <QtMultimediaKit/QAudioFormat>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>

using namespace std;


/**
  * @brief Класс используется для записи звука с микрофона
  */
class SoundRecorder : public QObject
{
    Q_OBJECT
public:
    /**
      * @brief В конструкторе устанавливается формат записи по умолчанию,
      *        создаётся и настраивается объект AudioInput
      * @details Для записи используется первое доступное устройство
      */
    SoundRecorder();
    ~SoundRecorder();
public slots:
    /**
      * @brief Начинает запись звука
      * @details Данные, полученные от устройства сохраняются в QByteArray
      *          После начала записи объект генерирует сигнал frameRecorded каждые frameLength миллисекунд
      */
    void startRecording();
    /**
      * @brief Завершение записи
      */
    void stopRecording();
private slots:
    /**
      * @brief Копирует последний записанный фрейм
      */
    void recordFrame();
signals:
    /**
      * @details Сигнал вызывается каждые frameLength секунд и содержит массив байт с записанным фреймом
      */
    void frameRecorded(QByteArray*);
private:
    /**
      * @brief Установка параметров записи по умолчанию
      */
    void defaultFormatSettings();
    QAudioInput* audioIn;
    QAudioFormat audioFormat;
    QByteArray* byteArray;
    QBuffer* buffer;
    quint64 currentPos;
    static const int frameLength = 50;
};

