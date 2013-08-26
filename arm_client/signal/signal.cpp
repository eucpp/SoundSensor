#include "signal.h"

Signal::Signal():
    bytes(),
    format()
{}

Signal::Signal(int n, const QAudioFormat& signalFormat):
    bytes(n * (signalFormat.sampleSize() / 8), 0),
    format(signalFormat)
{}

Signal::Signal(const QByteArray& byteArray, const QAudioFormat& signalFormat):
    bytes(byteArray),
    format(signalFormat)
{
    /*
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
    */
}

void Signal::setData(const QByteArray& byteArray, const QAudioFormat& signalFormat)
{
    bytes = byteArray;
    format = signalFormat;
}

char* Signal::data()
{
    return bytes.data();
}

const char *Signal::data() const
{
    return bytes.constData();
}

QAudioFormat Signal::getFormat() const
{
    return format;
}

void Signal::setFormat(const QAudioFormat &signalFormat)
{
    format = signalFormat;
}


Sample Signal::operator[](int i) throw(OutOfSignalRangeExc, SampleSizeUnset)
{
    if (i < 0 || i >= size())
    {
        throw OutOfSignalRangeExc();
    }
    if (!sampleSizeSet())
    {
        throw SampleSizeUnset();
    }
    return Sample(bytes.data() + i * sampleSize(), this);
}

const Sample Signal::operator[](int i) const throw(OutOfSignalRangeExc, SampleSizeUnset)
{
    if (i < 0 || i >= size())
    {
        throw OutOfSignalRangeExc();
    }
    return Sample(bytes.data() + i * sampleSize(), this);
}

bool Signal::operator==(const Signal &signal) const
{
    return ((bytes == signal.bytes) && (format == signal.format));
}

int Signal::sampleSize() const throw(SampleSizeUnset)
{
    if (!sampleSizeSet())
    {
        throw SampleSizeUnset();
    }
    return (format.sampleSize() / 8);
}

int Signal::sampleRate() const throw(SampleRateUnset)
{
    if (!sampleRateSet())
    {
        throw SampleRateUnset();
    }
    return format.sampleRate();
}

int Signal::size() const
{
    return (bytes.size() / sampleSize());
}

void Signal::resize(int n)
{
    n *= sampleSize();
    int oldSize = bytes.size();
    bytes.resize(n);
    if (n > oldSize)
    {
        for (int i = oldSize; i < n; i++)
        {
            bytes[i] = 0;
        }
    }
}

int Signal::time(int i) const throw(OutOfSignalRangeExc, SampleRateUnset)
{
    if (i < 0 || i >= size())
    {
        throw OutOfSignalRangeExc();
    }
    double samplesPerMs = static_cast<double>(sampleRate()) / 1000;
    return round(i / samplesPerMs);
}

Signal Signal::subSignal(int start, int length) const
{
    return Signal(bytes.mid(start, length), format);
}

bool Signal::sampleSizeSet() const
{
    return ((format.sampleSize() == 8) || (format.sampleSize() == 16));
}

bool Signal::sampleRateSet() const
{
    return (format.sampleRate() != -1);
}

