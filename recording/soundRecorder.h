#pragma once

#include "buildParam.h"

#include <iostream>
#include <QObject>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioInput>
    #include <QtMultimediaKit/QAudioFormat>
    #include <QtMultimediaKit/QAudioOutput>
    #include <QtMultimediaKit/QAudioDeviceInfo>
#else
    #include <QtMultimedia/QAudioInput>
    #include <QtMultimedia/QAudioFormat>
    #include <QtMultimedia/QAudioOutput>
    #include <QtMultimedia/QAudioDeviceInfo>
#endif

#include <QBuffer>
#include <QByteArray>
#include "../signal/signal.h"

using namespace std;


/**
  * Класс используется для записи звука с микрофона (поддерживается только моно запись).
  */
class SoundRecorder : public QObject
{
    Q_OBJECT
public:
    /**
      * Конструктор.
      * При создании нового объекта используется устройство и формат записи по умолчанию.
      */
    SoundRecorder();
    /**
      * При вызове этого конструктора, используется формат записи по умолчанию.
      *
      * @param device Устройство для записи
      */
    SoundRecorder(const QAudioDeviceInfo& device);
    /**
      * При вызове этого конструктора, используется устройство для записи по умолчанию.
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
    /**
      * Возвращает используемый в данный момент формат записи.
      */
    QAudioFormat getFormat() const;
    /**
      * Устанавливает новый формат записи.
      * Если в момент вызова метода идёт запись, она будет остановлена.
      */
    void setFormat(const QAudioFormat& format);
    /**
      * Возвращает используемое в данный момент устройство.
      */
    QAudioDeviceInfo getDevice() const;
    /**
      * Устанавливает новое устройство в качестве устройства записи.
      * Если в момент вызова метода идёт запись, она будет остановлена.
      */
    void setDevice(const QAudioDeviceInfo& device);
    /**
      * Устанавливает длину фрейма.
      * При записи звука, через промежутки времени, равные длине фрейма, генерируется сигнал
      * содержащий объект-сигнал, который хранит записанные байты.
      */
    void setFrameLength(int length);
    /**
      * Возвращает длину фрейма.
      */
    int getFrameLength() const;
    /**
      * Возвращает формат записи, используемый по умолчанию.
      */
    static QAudioFormat defaultAudioFormat();
public slots:
    /**
      * Начинает запись звука.
      * Данные, полученные от устройства сохраняются в объект Signal.
      * После начала записи объект генерирует сигнал frameRecorded каждые frameLength миллисекунд.
      */
    void start();
    /**
      * Завершение записи.
      */
    void stop();
signals:
    /**
      * Вызывается каждые frameLength секунд и содержит объект-сигнал с записанным фреймом.
      */
    void frameRecorded(Signal);
    /**
      * Вызывается после окончания записи и содержит объект-сигнал с записью.
      */
    void recordingStopped(Signal);
private slots:
    /**
      * Копирует последний записанный фрейм.
      */
    void recordFrame();
private:
    QAudioDeviceInfo audioDevice;
    QScopedPointer<QAudioInput> audioIn;
    QByteArray byteArray;
    QBuffer buffer;
    quint64 currentFramePos;

    static const int defaultFrameLength = 1000;
};

