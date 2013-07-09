#pragma once

#include <limits>
#include <QObject>
#include <pocketsphinx/cmdln_macro.h>
#include <pocketsphinx/pocketsphinx.h>
#include "signal.h"

/**
  * Класс-обёртка для библиотеки pocketsphinx.
  * Содержит методы для распознавания голосовых команд в звуковом сигнале.
  */
class VoiceCommandSensor : public QObject
{
    Q_OBJECT
public:
    /**
      * Класс исключений, бросаемых при ошибке инициализации pocketsphinx
      * в конструкторе класса.
      */
    class PocketSphinxInitExc
    {};
    /**
      * Класс исключений, бросаемых при ошибке распознавания команды
      */
    class PocketSphinxRecognizeExc
    {};
    /**
      * Структура, описывающая опознанную голосовую команду.
      *
      */
    struct Command
    {
        /**
          * Текст команды
          */
        QString command;
        /**
          * Точность распознавания (в диапозоне от 0 до 1)
          */
        double accuracy;
    };

    /**
      * Конструктор датчика команд.
      *
      * @param pathToHmm путь к файлу акустической модели
      * @param pathToLm путь к файлу языковой модели
      * @param pathToDict путь к файлу словаря
      */
    VoiceCommandSensor(QString pathToHmm, QString pathToLm, QString pathToDict)
        throw(PocketSphinxInitExc);
    ~VoiceCommandSensor();
public slots:
    /**
      * Метод пытается распознать голосовую команду в переданном сигнале.
      * После окончания работы генерирует сигнал commandRecognized.
      */
    Command recognize(Signal signal);
signals:
    /**
      * Сигнал, генерируемый после распознавания команды.
      */
    void commandRecognized(Command);
private:
    ps_decoder_t* recognizer;
    cmd_ln_t* config;
};
