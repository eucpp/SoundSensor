#include "signal.h"

Signal::Signal(QByteArray byteArray, QAudioFormat signalFormat):
    bytes(byteArray),
    bytesSetFlag(true),
    bytesFormat(signalFormat),
    values(NULL)
{}

Signal::Signal(double *vals, unsigned int valsSize):
    values(vals),
    size(valsSize),
    bytesSetFlag(false)
{}

// оператор возвращает значение, считая, что массив байт имеет формат:
// channels = 1; sample size = 8 bit; byte order = little endian; sample type = signed int
// to do: нормальный, форматозовисимый оператор доступа
double Signal::operator[](unsigned int i)
{
    if (values != NULL)
        return values[i];
    else
        return pcmToDouble(bytes[i]);
}

QAudioFormat Signal::getFormat()
{
    return bytesFormat;
}
void Signal::setFormat(QAudioFormat format)
{
    bytesFormat = format;
}

unsigned int Signal::getSize()
{
    if (bytesSetFlag)
        return bytes.size();
    return size;
}

QByteArray Signal::getBytes()
{
    if (!bytesSetFlag)
    {
        bytes = doublesToByteArray();
        bytesSetFlag = true;
    }
    return bytes;
}

double* Signal::getData()
{
    if (values == NULL)
        values = byteArrayToDoubles();
    return values;
}

// преобразование не учитывает формат массива байт
// используется формат по умолчанию:
// channels = 1; sample size = 8 bit; byte order = little endian; sample type = signed int
QByteArray Signal::doublesToByteArray()
{
    QByteArray byteArray;
    for (unsigned int i = 0; i < size; i++)
    {
        byteArray[i] = doubleToPcm(this->operator[](i));
    }
}

double* Signal::byteArrayToDoubles()
{
    int arraySize = bytes.size();
    double* doubleArray = new double[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        doubleArray[i] = this->operator[](i);
    }
    return doubleArray;
}

double inline Signal::pcmToDouble(int pcm)
{
    return static_cast<double>(pcm) / PCM8MaxAmplitude;
}
int inline Signal::doubleToPcm(double val)
{
    return static_cast<int>(round(val * PCM8MaxAmplitude));
}
