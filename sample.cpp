#include "sample.h"

Sample::Sample():
    value(0)
{}

Sample::Sample(double d):
    value(d)
{}

Sample::Sample(char pcm)
{
    value = pcmToDouble(pcm, 8);
}

Sample::Sample(short pcm, ByteOrder byteOrder)
{
    short newPcm = pcm;
    if (byteOrder == LittleEndian)
        newPcm =  qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    value = pcmToDouble(newPcm, 16);
}

Sample::Sample(unsigned char pcm)
{
    value = pcmToDouble(pcm - PCM8MaxAmplitude - 1, 8);
}

Sample::Sample(unsigned short pcm, ByteOrder byteOrder)
{
    short newPcm = pcm;
    if (byteOrder == LittleEndian)
        newPcm =  qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    value = pcmToDouble(newPcm - PCM16MaxAmplitude - 1, 16);
}

double Sample::toDouble() const
{
    return value;
}

float Sample::toFloat() const
{
    return static_cast<float>(value);
}

char Sample::toPcm8() const
{
    return static_cast<char>(doubleToPcm(value, 8));
}

short Sample::toPcm16(ByteOrder byteOrder) const
{
    if (byteOrder == LittleEndian)
    {
        short pcm;
        unsigned char* ptr = reinterpret_cast<unsigned char*>(&pcm);
        qToLittleEndian(static_cast<short>(doubleToPcm(value, 16)), ptr);
        return pcm;
    }
    else
    {
        short pcm;
        unsigned char* ptr = reinterpret_cast<unsigned char*>(&pcm);
        qToBigEndian(static_cast<short>(doubleToPcm(value, 16)), ptr);
        return pcm;
    }
}

unsigned char Sample::toUPcm8() const
{
    return static_cast<unsigned char>(doubleToPcm(value, 8) + PCM8MaxAmplitude + 1);
}

unsigned short Sample::toUPcm16(ByteOrder byteOrder) const
{
    if (byteOrder == LittleEndian)
    {
        unsigned short pcm;
        unsigned char* ptr = reinterpret_cast<unsigned char*>(&pcm);
        qToLittleEndian(static_cast<unsigned short>(doubleToPcm(value, 16) + PCM16MaxAmplitude + 1), ptr);
        return pcm;
    }
    else
    {
        unsigned short pcm;
        unsigned char* ptr = reinterpret_cast<unsigned char*>(&pcm);
        qToBigEndian(static_cast<unsigned short>(doubleToPcm(value, 16) + PCM16MaxAmplitude + 1), ptr);
        return pcm;
    }
}

bool Sample::operator==(const Sample &sample) const
{
    const double eps = 0.01;
    return (qAbs(this->toDouble() - sample.toDouble()) < eps);
}

double Sample::pcmToDouble(int pcm, int pcmSize)
{
    if (pcmSize == 8)
        if (pcm == -128)
            return -1.0;
        else
            return static_cast<double>(pcm) / PCM8MaxAmplitude;
    else if (pcmSize == 16)
        if (pcm == -32768)
            return -1.0;
        else
            return static_cast<double>(pcm) / PCM16MaxAmplitude;
}

int Sample::doubleToPcm(double val, int pcmSize)
{
    if (pcmSize == 8)
        if (val == -1.0)
            return -128;
        else
            return static_cast<int>(round(val * PCM8MaxAmplitude));
    else if (pcmSize == 16)
        if (val == -1.0)
            return -32768;
        else
            return static_cast<int>(round(val * PCM16MaxAmplitude));
}
