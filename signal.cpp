#include "signal.h"

Signal::Signal(QByteArray byteArray, QAudioFormat signalFormat):
    bytes(byteArray),
    bytesFormat(signalFormat),
    bytesSetFlag(true),
    valuesSetFlag(false),
    values(NULL)
{}

Signal::Signal(double *vals, unsigned int valsSize):
    values(vals),
    valuesSize(valsSize),
    valuesSetFlag(true),
    bytesSetFlag(false)
{}

// to do: тест для этой функции!
double Signal::operator[](unsigned int i) throw(OutOfSignalRangeExc)
{
    if (valuesSetFlag)
    {
        if (i >= valuesSize || i < 0)
            throw OutOfSignalRangeExc();
        return values[i];
    }
    else if (bytesSetFlag)
    {
        int sampleSize = bytesFormat.sampleSize() / 8;
        char* val = new char(4);
        int valPos = i * sampleSize;
        if (valPos >= bytes.size() || valPos < 0)
            throw OutOfSignalRangeExc();
        for (int i = 0; i < 4; ++i)
        {
            if (bytesFormat.byteOrder() == QAudioFormat::LittleEndian)
            {
                if (i < sampleSize)
                    val[i] = bytes[valPos + i];
                else
                    val[i] = 0;
            }
            else if (bytesFormat.byteOrder() == QAudioFormat::BigEndian)
            {
                if (i < sampleSize)
                    val[i] = bytes[valPos + (sampleSize - 1) - i];
                else
                    val[i] = 0;
            }
        }
        int* intVal = reinterpret_cast<int*>(val);
        if (bytesFormat.sampleType() == QAudioFormat::SignedInt)
        {
            if (sampleSize == 1)
                *intVal += 128;
            else if (sampleSize == 2)
                *intVal += 32768;
        }
        return pcmToDouble(*intVal, bytesFormat.sampleSize());
    }
    else
        throw OutOfSignalRangeExc();
}

QAudioFormat Signal::getFormat()
{
    return bytesFormat;
}
void Signal::setFormat(QAudioFormat format)
{
    if (bytesSetFlag)
    {
        // здесь надо бы ещё проверить, не одинаковы ли форматы
        convertByteArray(format);
    }
    else
        bytesFormat = format;
}

unsigned int Signal::size()
{
    if (bytesSetFlag)
        return bytes.size();
    return valuesSize;
}

QByteArray Signal::getBytes()
{
    if (!bytesSetFlag)
    {
        doublesToByteArray();
    }
    return bytes;
}

double* Signal::getData()
{
    if (values == NULL)
        byteArrayToDoubles();
    return values;
}

void Signal::convertByteArray(QAudioFormat newFormat)
{
    if (!valuesSetFlag)
        byteArrayToDoubles();
    bytesFormat = newFormat;
    doublesToByteArray();
}

void Signal::doublesToByteArray()
{
    for (unsigned int i = 0; i < valuesSize; i++)
    {
        int intVal = doubleToPcm(values[i], bytesFormat.sampleSize());
        int* val = &intVal;
        int sampleSize = bytesFormat.sampleSize() / 8;
        if (bytesFormat.sampleType() == QAudioFormat::SignedInt)
        {
            if (sampleSize == 1)
                *val -= 128;
            else if (sampleSize == 2)
                *val -= 32768;
        }
        char* valBytes = reinterpret_cast<char*>(val);
        int valPos = i * sampleSize;
        for (int i = 0; i < sampleSize; ++i)
        {
            if (bytesFormat.byteOrder() == QAudioFormat::LittleEndian)
                bytes[valPos + i] =  valBytes[i];
            else if (bytesFormat.byteOrder() == QAudioFormat::BigEndian)
                bytes[valPos + (sampleSize - 1) - i] =  valBytes[i];
        }
    }
    bytesSetFlag = true;
}

void Signal::byteArrayToDoubles()
{
    valuesSize = bytes.size() / (bytesFormat.sampleSize() / 8);
    values = new double[valuesSize];
    for (int i = 0; i < valuesSize; i++)
    {
        values[i] = this->operator[](i);
    }
    valuesSetFlag = true;
}

double inline Signal::pcmToDouble(int pcm, int pcmSize)
{
    if (pcmSize == 8)
        return static_cast<double>(pcm) / PCM8MaxAmplitude;
    else if (pcmSize == 16)
        return static_cast<double>(pcm) / PCM16MaxAmplitude;
}
int inline Signal::doubleToPcm(double val, int pcmSize)
{
    if (pcmSize == 8)
        return static_cast<int>(round(val * PCM8MaxAmplitude));
    else if (pcmSize == 16)
        return static_cast<int>(round(val * PCM16MaxAmplitude));
}
