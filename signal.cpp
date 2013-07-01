#include "signal.h"

Signal::Signal():
    samples()
{}

Signal::Signal(int n):
    samples()
{
    samples.resize(n);
}

Signal::Signal(double* array, int arraySize):
    samples(arraySize)
{
    init(array);
}

Signal::Signal(float* array, int arraySize):
    samples(arraySize)
{
    init(array);
}

Signal::Signal(char* array, int arraySize):
    samples(arraySize)
{
    init(array);
}

Signal::Signal(short* array, int arraySize, Sample::ByteOrder byteOrder):
    samples(arraySize)
{
    for (int i = 0; i < samples.size(); i++)
        samples[i].setPcm16(array[i], byteOrder);
}

Signal::Signal(unsigned char* array, int arraySize):
    samples(arraySize)
{
    init(array);
}

Signal::Signal(unsigned short* array, int arraySize, Sample::ByteOrder byteOrder):
    samples(arraySize)
{
    for (int i = 0; i < samples.size(); i++)
        samples[i].setUPcm16(array[i], byteOrder);
}

Signal::Signal(const QByteArray& byteArray, const QAudioFormat& format):
    samples()
{
    int sampleSize = format.sampleSize();
    if (sampleSize == 8)
        samples.resize(byteArray.size());
    else if (sampleSize == 16)
        samples.resize(byteArray.size() / 2);
    Sample::ByteOrder byteOrd = Sample::LittleEndian;
    if (format.byteOrder() == QAudioFormat::BigEndian)
        byteOrd = Sample::BigEndian;
    for (int i = 0; i < size(); i++)
    {
        if (sampleSize == 8)
            samples[i] = byteArray[i];
        else if (sampleSize == 16)
        {
            unsigned char bytes[2];
            bytes[0] = byteArray[2 * i];
            bytes[1] = byteArray[2 * i + 1];
            short *ptr = reinterpret_cast<short*>(&bytes);
            if (format.sampleType() == QAudioFormat::SignedInt)
                samples[i].setPcm16(ptr[0], byteOrd);
            else
                samples[i].setUPcm16(ptr[0], byteOrd);
        }
    }
}

double* Signal::toDoubleArray() const
{
    double* array = new double[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toDouble();
    return array;
}

float* Signal::toFloatArray() const
{
    float* array = new float[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toFloat();
    return array;
}

char* Signal::toPcm8Array() const
{
    char* array = new char[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toPcm8();
    return array;
}

short* Signal::toPcm16Array(Sample::ByteOrder byteOrder) const
{
    short* array = new short[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toPcm16(byteOrder);
    return array;
}

unsigned char* Signal::toUPcm8Array() const
{
    unsigned char* array = new unsigned char[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toUPcm8();
    return array;
}

unsigned short* Signal::toUPcm16Array(Sample::ByteOrder byteOrder) const
{
    unsigned short* array = new unsigned short[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toUPcm16(byteOrder);
    return array;
}

QByteArray Signal::toByteArray(const QAudioFormat &format)
{
    if (format.sampleSize() == 8)
    {
        return QByteArray(toPcm8Array(), size());
    }
    else if (format.sampleSize() == 16)
    {
        Sample::ByteOrder byteOrd = Sample::LittleEndian;
        if (format.byteOrder() == QAudioFormat::BigEndian)
            byteOrd = Sample::BigEndian;
        short* bytes = toPcm16Array(byteOrd);
        return QByteArray(reinterpret_cast<char*>(bytes), size() * 2);
    }
}

Sample& Signal::operator[](int i) throw(OutOfSignalRangeExc)
{
    if (i < 0 || i >= size())
        throw OutOfSignalRangeExc();
    return samples[i];
}

const Sample& Signal::operator[](int i) const throw(OutOfSignalRangeExc)
{
    if (i < 0 || i >= size())
        throw OutOfSignalRangeExc();
    return samples[i];
}

bool Signal::operator==(const Signal &signal) const
{
    return (samples == signal.samples);
}

int Signal::size() const
{
    return samples.size();
}

void Signal::resize(int n)
{
    samples.resize(n);
}

Signal Signal::subSignal(int start, int length) const
{
    return Signal(samples.mid(start, length));
}

Signal::Signal(const QVector<Sample> &samplesVector)
{
    samples = samplesVector;
}
