#include "spectrogram.h"

Spectrogram::Spectrogram(int size):
    frequencies(size)
{}

Frequency& Spectrogram::operator[](int i)
{
    return frequencies[i];
}

int Spectrogram::size() const
{
    return frequencies.size();
}
