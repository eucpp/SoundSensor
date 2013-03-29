#pragma once

//#include <QObject>
#include <QVector>

/**
  * Структура, используемая для хранения данных о частоте и её амплитуде
  */
struct Frequency
{
    qreal amplitude;
    qreal frequency;
};

/**
  * Контейнер для массива данных, представляющих спектрограмму
  */
class Spectrogram
{
public:
    Spectrogram(int size);
    Frequency& operator[](int i);
    int size() const;
private:
    QVector<Frequency> frequencies;
};

