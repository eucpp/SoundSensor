#include "sample.h"

Sample::Sample():
    value(0),
    pcmSize(PCM16)
{}

Sample::Sample(double d):
    pcmSize(PCM16)
{
    value = doubleToPcm(d, pcmSize);
}

Sample::Sample(char pcm)
{
    pcmSize = PCM8;
    value = pcm;
}

Sample::Sample(short pcm, ByteOrder byteOrder)
{
    pcmSize = PCM16;
    short newPcm = pcm;
    if (byteOrder == LittleEndian)
        newPcm =  qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    value = newPcm;
}

Sample::Sample(unsigned char pcm)
{
    pcmSize = PCM8;
    value = pcm - PCM8MaxAmplitude - 1;
}

Sample::Sample(unsigned short pcm, ByteOrder byteOrder)
{
    pcmSize = PCM16;
    short newPcm = pcm;
    if (byteOrder == LittleEndian)
        newPcm =  qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    value = newPcm - PCM16MaxAmplitude - 1;
}

double Sample::toDouble() const
{
    return pcmToDouble(value, pcmSize);
}

float Sample::toFloat() const
{
    return static_cast<float>(pcmToDouble(value, pcmSize));
}

fixed_point Sample::toFixedPoint() const
{
    return fixed_point(toDouble());
}

char Sample::toPcm8() const
{
    if (pcmSize == PCM8)
        return static_cast<char>(value);
    else if (pcmSize == PCM16)
    {
        double d = pcmToDouble(value, PCM16);
        return static_cast<char>(doubleToPcm(d, PCM8));
    }
}

short Sample::toPcm16(ByteOrder byteOrder) const
{
    if (pcmSize == PCM16)
        if (byteOrder == LittleEndian)
            return qToLittleEndian(value);
        else
            return qToBigEndian(value);
    else if (pcmSize == PCM8)
    {
        double d = pcmToDouble(value, PCM8);
        short pcm16 = static_cast<short>(doubleToPcm(d, PCM16));
        if (byteOrder == LittleEndian)
            return qToLittleEndian(pcm16);
        else
            return qToBigEndian(pcm16);
    }
}

unsigned char Sample::toUPcm8() const
{
    if (pcmSize == PCM8)
        return static_cast<unsigned char>(value) + PCM8MaxAmplitude + 1;
    else if (pcmSize == PCM16)
    {
        double d = pcmToDouble(value, PCM16);
        return static_cast<unsigned short>(doubleToPcm(d, PCM8)) + PCM8MaxAmplitude + 1;
    }
}

unsigned short Sample::toUPcm16(ByteOrder byteOrder) const
{ 
    if (pcmSize == PCM16)
    {
        unsigned short uval = static_cast<unsigned short>(value) + PCM16MaxAmplitude + 1;
        if (byteOrder == LittleEndian)
            return qToLittleEndian(uval);
        else
            return qToBigEndian(uval);
    }
    else if (pcmSize == PCM8)
    {
        double d = pcmToDouble(value, PCM8);
        short pcm16 = static_cast<unsigned short>(doubleToPcm(d, PCM16) + PCM16MaxAmplitude + 1);
        if (byteOrder == LittleEndian)
            return qToLittleEndian(pcm16);
        else
            return qToBigEndian(pcm16);
    }
}

bool Sample::operator==(const Sample &sample) const
{
    return ((pcmSize == sample.pcmSize) && (value == value));
}

void Sample::setSampleSize(Sample::PCMSize size)
{
    if (size != pcmSize)
    {
        double d = pcmToDouble(value, pcmSize);
        value = doubleToPcm(d, size);
        pcmSize = size;
    }
}
Sample::PCMSize Sample::getSampleSize()
{
    return pcmSize;
}

double Sample::pcmToDouble(int pcm, PCMSize size)
{
    if (size == PCM8)
        if (pcm == -128)
            return -1.0;
        else
            return static_cast<double>(pcm) / PCM8MaxAmplitude;
    else if (size == PCM16)
        if (pcm == -32768)
            return -1.0;
        else
            return static_cast<double>(pcm) / PCM16MaxAmplitude;
}

int Sample::doubleToPcm(double val, PCMSize size)
{
    if (size == PCM8)
        if (val == -1.0)
            return -128;
        else
            return static_cast<int>(round(val * PCM8MaxAmplitude));
    else if (size == PCM16)
        if (val == -1.0)
            return -32768;
        else
            return static_cast<int>(round(val * PCM16MaxAmplitude));
}

