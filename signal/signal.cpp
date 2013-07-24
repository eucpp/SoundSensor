#include "signal.h"

Signal::Signal():
    samples()
{}

Signal::Signal(int n, int sampleRate):
    samples()
{
    samples.resize(n);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
}

Signal::Signal(double* array, int arraySize, int sampleRate):
    samples(arraySize)
{
    init(array);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
}

Signal::Signal(float* array, int arraySize, int sampleRate):
    samples(arraySize)
{
    init(array);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
}

Signal::Signal(char* array, int arraySize, int sampleRate):
    samples(arraySize)
{
    init(array);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(8);
    format.setSampleType(QAudioFormat::SignedInt);
}

Signal::Signal(short* array, int arraySize, QAudioFormat::Endian byteOrder, int sampleRate):
    samples(arraySize)
{
    for (int i = 0; i < samples.size(); i++)
        samples[i].setPcm16(array[i], byteOrder);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(byteOrder);
}

Signal::Signal(unsigned char* array, int arraySize, int sampleRate):
    samples(arraySize)
{
    init(array);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(8);
    format.setSampleType(QAudioFormat::UnSignedInt);
}

Signal::Signal(unsigned short* array, int arraySize, QAudioFormat::Endian byteOrder, int sampleRate):
    samples(arraySize)
{
    for (int i = 0; i < samples.size(); i++)
        samples[i].setUPcm16(array[i], byteOrder);
    format.setChannels(1);
    format.setSampleRate(sampleRate);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::UnSignedInt);
    format.setByteOrder(byteOrder);
}

Signal::Signal(const QByteArray& byteArray, const QAudioFormat& signalFormat):
    samples()
{
    format = signalFormat;
    int sampleSize = format.sampleSize();
    if (sampleSize == 8)
        samples.resize(byteArray.size());
    else if (sampleSize == 16)
        samples.resize(byteArray.size() / 2);
    QAudioFormat::Endian byteOrd = format.byteOrder();
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
        array[i] = samples[i].toFloat();
    return array;
}

float* Signal::toFloatArray() const
{
    float* array = new float[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toFloat();
    return array;
}

fixed_point *Signal::toFixedPointArray() const
{
    fixed_point* array = new fixed_point[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toFixedPoint();
    return array;
}

char* Signal::toPcm8Array() const
{
    char* array = new char[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toPcm8();
    return array;
}

short* Signal::toPcm16Array(QAudioFormat::Endian byteOrder) const
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

unsigned short* Signal::toUPcm16Array(QAudioFormat::Endian byteOrder) const
{
    unsigned short* array = new unsigned short[size()];
    for (int i = 0; i < size(); i++)
        array[i] = samples[i].toUPcm16(byteOrder);
    return array;
}

QByteArray Signal::toByteArray()
{
    if (format.sampleSize() == 8)
    {
        return QByteArray(toPcm8Array(), size());
    }
    else if (format.sampleSize() == 16)
    {
        short* bytes = toPcm16Array(format.byteOrder());
        return QByteArray(reinterpret_cast<char*>(bytes), size() * 2);
    }
}

QAudioFormat Signal::getFormat()
{
    return format;
}

void Signal::setFormat(const QAudioFormat &signalFormat)
{
    format = signalFormat;
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
    return ((samples == signal.samples) && (format == signal.format));
}

int Signal::size() const
{
    return samples.size();
}

void Signal::resize(int n)
{
    samples.resize(n);
}

int Signal::time(int i)
{
    double samplesPerMs = static_cast<double>(format.sampleRate()) / 1000;
    return round(i / samplesPerMs);
}

Signal Signal::subSignal(int start, int length) const
{
    return Signal(samples.mid(start, length), format);
}

Signal::Signal(const QVector<Sample> &samplesVector, const QAudioFormat& signalFormat)
{
    samples = samplesVector;
    format = signalFormat;
}