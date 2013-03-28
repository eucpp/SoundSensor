#pragma once

//#include <QObject>
#include <QVector>

struct Frequency
{
    qreal amplitude;
    qreal frequency;
};

class Spectrogram
{
public:
    Spectrogram(int size);
    Frequency& operator[](int i);
    int size() const;
private:
    QVector<Frequency> frequencies;
};

