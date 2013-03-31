#include "utils.h"

const int PCM4MaxAmplitude = 128;


float pcmToFloat(int pcm)
{
    return static_cast<float>(pcm / PCM4MaxAmplitude);
}
double pcmToDouble(int pcm)
{
    return static_cast<double>(pcm / PCM4MaxAmplitude);
}

double* byteArrayToDouble(QByteArray byteArray)
{
    int size = byteArray.size();
    double* doubleArray = new double[size];
    for (int i = 0; i < size; i++)
    {
        doubleArray[i] = pcmToDouble(byteArray[i]);
    }
    return doubleArray;
}
