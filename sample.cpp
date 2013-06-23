#include "sample.h"

Sample::Sample():
    value(0),
    byteOrd(LittleEndian)
{}

Sample::Sample(double d):
    value(d),
    byteOrd(LittleEndian)
{}

Sample::Sample(char pcm):
    byteOrd(LittleEndian)
{
    value = pcmToDouble(pcm, 8);
}

Sample::Sample(short pcm):
    byteOrd(LittleEndian)
{
    value = pcmToDouble(pcm, 16);
}

Sample::Sample(unsigned char pcm):
    byteOrd(LittleEndian)
{
    value = pcmToDouble(pcm - PCM8MaxAmplitude - 1, 8);
}

Sample::Sample(unsigned short pcm):
    byteOrd(LittleEndian)
{
    value = pcmToDouble(pcm - PCM16MaxAmplitude - 1, 16);
}

double Sample::toDouble()
{
    return value;
}

float Sample::toFloat()
{
    return static_cast<float>(value);
}

char Sample::toPcm8()
{
    return static_cast<char>(doubleToPcm(value, 8));
}

short Sample::toPcm16()
{
    if (byteOrder() == LittleEndian)
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

unsigned char Sample::toUPcm8()
{
    return static_cast<unsigned char>(doubleToPcm(value, 8) + PCM8MaxAmplitude + 1);
}

unsigned short Sample::toUPcm16()
{
    if (byteOrder() == LittleEndian)
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

void Sample::setByteOrder(ByteOrder order)
{
    byteOrd = order;
}

Sample::ByteOrder Sample::byteOrder()
{
    return byteOrd;
}

double inline Sample::pcmToDouble(int pcm, int pcmSize)
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

int inline Sample::doubleToPcm(double val, int pcmSize)
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
