#include "sample.h"

const int Sample::PCM8MaxAmplitude = 127;
const int Sample::PCM16MaxAmplitude = 32767;
const float Sample::eps = 0.001;

Sample::Sample():
    type(Unset),
    pcmValue(0),
    floatValue(0)
{}

Sample::Sample(float f):
    type(Float),
    pcmValue(0),
    floatValue(f)
{}

Sample::Sample(double d):
    type(Float),
    pcmValue(0),
    floatValue(static_cast<float>(d))
{}

Sample::Sample(char pcm):
    type(PCM8),
    pcmValue(pcm),
    floatValue(0)
{}

Sample::Sample(short pcm, QAudioFormat::Endian byteOrder):
    type(PCM16),
    floatValue(0)
{
    short newPcm = pcm;
    if (byteOrder == QAudioFormat::LittleEndian)
        newPcm =  qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    pcmValue = newPcm;
}

void Sample::setFloat(float value)
{
    if (type == Unset)
    {
        type = Float;
        floatValue = value;
    }
    else
    {
        if (type != Float)
            return;
        floatValue = value;
    }
}

void Sample::setPcm8(char pcm)
{
    if (type == Unset)
    {
        type = PCM8;
        pcmValue = pcm;
    }
    else
    {
        if (type != PCM8)
            return;
        pcmValue = pcm;
    }
}

void Sample::setUPcm8(unsigned char pcm)
{
    pcm = pcm - PCM8MaxAmplitude - 1;
    if (type == Unset)
    {
        type = PCM8;
        pcmValue = pcm;
    }
    else
    {
        if (type != PCM8)
            return;
        pcmValue = pcm;
    }
}

void Sample::setPcm16(short pcm, QAudioFormat::Endian byteOrder)
{
    short newPcm = pcm;
    if (byteOrder == QAudioFormat::LittleEndian)
        newPcm = qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    if (type == Unset)
    {
        type = PCM16;
        pcmValue = newPcm;
    }
    else
    {
        if (type != PCM16)
            return;
        pcmValue = newPcm;
    }
}

void Sample::setUPcm16(unsigned short pcm, QAudioFormat::Endian byteOrder)
{
    short newPcm = pcm;
    if (byteOrder == QAudioFormat::LittleEndian)
        newPcm = qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    newPcm = newPcm - PCM16MaxAmplitude - 1;
    if (type == Unset)
    {
        type = PCM16;
        pcmValue = newPcm;
    }
    else
    {
        if (type != PCM16)
            return;
        pcmValue = newPcm;
    }
}


Sample::Sample(unsigned char pcm):
    type(PCM8),
    floatValue(0)
{
    pcmValue = pcm - PCM8MaxAmplitude - 1;
}

Sample::Sample(unsigned short pcm, QAudioFormat::Endian byteOrder):
    type(PCM8),
    floatValue(0)
{
    short newPcm = pcm;
    if (byteOrder == QAudioFormat::LittleEndian)
        newPcm =  qFromLittleEndian(pcm);
    else
        newPcm = qFromBigEndian(pcm);
    pcmValue = newPcm - PCM16MaxAmplitude - 1;
}

/*
double Sample::toDouble() const
{
    return pcmToDouble(value, pcmSize);
}
*/

float Sample::toFloat() const
{
    if (type == Unset)
        return 0;
    else if (type == PCM8)
        return pcmToFloat(pcmValue, 8);
    else if (type == PCM16)
        return pcmToFloat(pcmValue, 16);
    else if (type == Float)
        return floatValue;
}

fixed_point Sample::toFixedPoint() const
{
    return fixed_point(toFloat());
}

char Sample::toPcm8() const
{
    if (type == Unset)
        return 0;
    else if (type == PCM8)
        return static_cast<char>(pcmValue);
    else if (type == PCM16)
    {
        double d = pcmToFloat(pcmValue, 16);
        return static_cast<char>(floatToPcm(d, 8));
    }
    else if (type == Float)
        return static_cast<char>(floatToPcm(floatValue, 8));
}

short Sample::toPcm16(QAudioFormat::Endian byteOrder) const
{
    if (type == Unset)
        return 0;
    else if (type == PCM8)
    {
        float f = pcmToFloat(pcmValue, 8);
        short pcm16 = static_cast<short>(floatToPcm(f, 16));
        if (byteOrder == QAudioFormat::LittleEndian)
            return qToLittleEndian(pcm16);
        else
            return qToBigEndian(pcm16);
    }
    else if (type == PCM16)
        if (byteOrder == QAudioFormat::LittleEndian)
            return qToLittleEndian(pcmValue);
        else
            return qToBigEndian(pcmValue);
    else if (type == Float)
    {
        short pcm16 = static_cast<short>(floatToPcm(floatValue, 16));
        if (byteOrder == QAudioFormat::LittleEndian)
            return qToLittleEndian(pcm16);
        else
            return qToBigEndian(pcm16);
    }
}

unsigned char Sample::toUPcm8() const
{
    return static_cast<unsigned char>(toPcm8() + PCM8MaxAmplitude + 1);
}

unsigned short Sample::toUPcm16(QAudioFormat::Endian byteOrder) const
{ 
    short pcm16 = toPcm16();
    unsigned short upcm16 = static_cast<unsigned short>(pcm16 + PCM16MaxAmplitude + 1);
    if (byteOrder == QAudioFormat::LittleEndian)
        return qToLittleEndian(upcm16);
    else
        return qToBigEndian(upcm16);
}

bool Sample::operator==(const Sample &sample) const
{
    if (type != sample.type)
        return false;
    if (type == Float)
        return (qAbs(floatValue - sample.floatValue) < eps);
    else
        return (pcmValue == sample.pcmValue);
}

/*
Sample& Sample::operator=(const Sample &sample)
{
    if (type == sample.type)
    {
        pcmValue = sample.pcmValue;
        floatValue = sample.floatValue;
    }
    return *this;
}
*/

/*
void Sample::setSampleSize(Sample::PCMSize size)
{
    if (size != pcmSize)
    {
        double d = pcmToDouble(value, pcmSize);
        value = doubleToPcm(d, size);
        pcmSize = size;
    }
}
*/

Sample::Type Sample::getSampleType() const
{
    return type;
}

float Sample::pcmToFloat(int pcm, int size)
{
    if (size == 8)
        if (pcm == -128)
            return -1.0;
        else
            return static_cast<float>(pcm) / PCM8MaxAmplitude;
    else if (size == 16)
        if (pcm == -32768)
            return -1.0;
        else
            return static_cast<float>(pcm) / PCM16MaxAmplitude;
}

int Sample::floatToPcm(float val, int size)
{
    if (size == 8)
        if (val == -1.0)
            return -128;
        else
            return static_cast<int>(round(val * PCM8MaxAmplitude));
    else if (size == 16)
        if (val == -1.0)
            return -32768;
        else
            return static_cast<int>(round(val * PCM16MaxAmplitude));
}

