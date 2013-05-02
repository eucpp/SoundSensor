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
  * Класс используется для записи звука с микрофона (поддерживается только моно запись)
  */
class SoundRecorder : public QObject
{
    Q_OBJECT
public:
    /**
      * Конструктор.
      * При создании нового объекта используется устройство и формат записи по умолчанию
      */
    SoundRecorder();
    /**
      * При вызове этого конструктора, используется формат записи по умолчанию
      *
      * @param device Устройство для записи
      */
    SoundRecorder(const QAudioDeviceInfo& device);
    /**
      * При вызове этого конструктора, используется устройство для записи по умолчанию
      *
      * @param format Формат записи
      */
    SoundRecorder(const QAudioFormat& format);
    /**
      * @param device Устройство для записи
      * @param format Формат записи
      */
    SoundRecorder(const QAudioDeviceInfo& device, const QAudioFormat& format);
    /**
      * Возвращает весь записанный сигнал, если запись остановлена,
      * или доступный для чтения участок записи (от начала) если запись продолжается.
      */
    Signal getSignal() const;
    QAudioFormat getAudioFormat() const;
    QAudioDeviceInfo getAudioDevice() const;
    /**
      * Устанавливает длину фрейма.
      * При записи звука, через промежутки времени, равные длине фрейма, генерируется сигнал
      * содержащий объект-сигнал, который хранит записанные байты.
      */
    void setFrameLength(int length);
    int getFrameLength() const;
    /**
      * Возвращает формат записи, используемый по умолчанию
      */
    static QAudioFormat defaultAudioFormat();
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
    /**
      * Вызывается после окончания записи и содержит объект-сигнал с записью.
      */
    void recordingStopped(Signal);
private:
    QAudioDeviceInfo audioDevice;
    QAudioInput audioIn;
    QByteArray byteArray;
    QBuffer buffer;
    quint64 currentFramePos;
    static const int defaultFrameLength = 128;
};

