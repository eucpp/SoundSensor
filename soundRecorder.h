#pragma once

#include <iostream>
#include <QObject>
#include <QtMultimediaKit/QAudioInput>
#include <QtMultimediaKit/QAudioFormat>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include "signal.h"

using namespace std;


/**
  * @brief Класс используется для записи звука с микрофона
  */
class SoundRecorder : public QObject
{
    Q_OBJECT
public:
    /**
      * В конструкторе устанавливается формат записи по умолчанию,
      * создаётся и настраивается объект AudioInput.
      * Для записи используется первое доступное устройство
      */
    SoundRecorder(QAudioDeviceInfo& device);
    ~SoundRecorder();
    Signal getSignal();
    QAudioFormat getAudioFormat() const;
public slots:
    /**
      * Начинает запись звука.
      * Данные, полученные от устройства сохраняются в QByteArray.
      * После начала записи объект генерирует сигнал frameRecorded каждые frameLength миллисекунд.
      */
    void startRecording();
    /**
      * Завершение записи.
      */
    void stopRecording();
private slots:
    /**
      * Копирует последний записанный фрейм.
      */
    void recordFrame();
signals:
    /**
      * Вызывается каждые frameLength секунд и содержит объект-сигнал с записанным фреймом.
      */
    void frameRecorded(Signal);
private:
    /**
      * Установка параметров записи по умолчанию.
      */
    void defaultFormatSettings();

    QAudioInput* audioIn;
    QAudioFormat audioFormat;
    QAudioDeviceInfo audioDevice;
    QByteArray* byteArray;
    QBuffer* buffer;
    quint64 currentFramePos;
    static const int frameLength = 128;
};

