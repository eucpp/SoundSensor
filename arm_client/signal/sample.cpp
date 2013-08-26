#include "sample.h"

const int Sample::PCM8MaxAmplitude = 127;
const int Sample::PCM8MinAmplitude = -128;
const int Sample::PCM16MaxAmplitude = 32767;
const int Sample::PCM16MinAmplitude = -32768;



int Sample::toInt() const
{
    if (signal->sampleSize() == 1)
    {
        if (signal->getFormat().sampleType() == QAudioFormat::SignedInt)
        {
            return constSampleData[0];
        }
        else
        {
            return static_cast<unsigned char>(sampleData[0]);
        }
    }
    else if (signal->sampleSize() == 2)
    {
        if (signal->getFormat().sampleType() == QAudioFormat::SignedInt)
        {
            const short* val = reinterpret_cast<const short*>(constSampleData);
            if (signal->getFormat().byteOrder() == QAudioFormat::LittleEndian)
            {
                return qFromLittleEndian(*val);
            }
            else
            {
                return qFromBigEndian(*val);
            }
        }
        else
        {
            const unsigned short* val = reinterpret_cast<const unsigned short*>(sampleData);
            if (signal->getFormat().byteOrder() == QAudioFormat::LittleEndian)
            {
                return qFromLittleEndian(*val);
            }
            else
            {
                return qFromBigEndian(*val);
            }
        }
    }
    else
    {
        throw Signal::SampleSizeUnset();
    }
}

bool Sample::operator==(const Sample &sample) const
{
    if (signal->sampleSize() != sample.signal->sampleSize())
    {
        return false;
    }
    if (signal->getFormat().sampleType() != sample.signal->getFormat().sampleType())
    {
        return false;
    }
    else
    {
        return (this->toInt() == sample.toInt());
    }
}

bool Sample::operator==(int val) const
{
    return (this->toInt() == val);
}

Sample& Sample::operator=(const Sample& sample)
{
    if (this == &sample)
    {
        return *this;
    }
    if (signal->sampleSize() != sample.signal->sampleSize())
    {
        throw DifferentSampleSizes();
    }
    if (signal->sampleSize() == 1)
    {
        sampleData[0] = sample.sampleData[0];
    }
    else if (signal->sampleSize() == 2)
    {
        if (signal->getFormat().byteOrder() == sample.signal->getFormat().byteOrder())
        {
            sampleData[0] = sample.sampleData[0];
            sampleData[1] = sample.sampleData[1];
        }
        else
        {
            sampleData[0] = sample.sampleData[1];
            sampleData[1] = sample.sampleData[0];
        }
    }

    return *this;
}

Sample *Sample::operator=(int val)
{
    if (signal->sampleSize() == 1)
    {
        if (signal->getFormat().sampleType() == QAudioFormat::SignedInt)
        {
            if ((val < PCM8MinAmplitude) || (val > PCM8MaxAmplitude))
            {
                throw OutOfRangeValue();
            }
            sampleData[0] = static_cast<char>(val);
        }
        else
        {
            if ((val < 0) || (val > (PCM8MaxAmplitude + qAbs(PCM8MinAmplitude))))
            {
                throw OutOfRangeValue();
            }
            sampleData[0] = static_cast<unsigned char>(val);
        }
    }
    else if (signal->sampleSize() == 2)
    {
        if (signal->getFormat().sampleType() == QAudioFormat::SignedInt)
        {
            if ((val < PCM16MinAmplitude) || (val > PCM16MaxAmplitude))
            {
                throw OutOfRangeValue();
            }
            short shVal = static_cast<short>(val);
            if (signal->getFormat().byteOrder() == QAudioFormat::LittleEndian)
            {
                short tmp = qToLittleEndian(shVal);
                char* pTmp = reinterpret_cast<char*>(&tmp);
                sampleData[0] = pTmp[0];
                sampleData[1] = pTmp[1];
            }
            else
            {
                short tmp = qToBigEndian(shVal);
                char* pTmp = reinterpret_cast<char*>(&tmp);
                sampleData[0] = pTmp[0];
                sampleData[1] = pTmp[1];
            }
        }
        else
        {
            if ((val < 0) || (val > PCM16MaxAmplitude + qAbs(PCM16MinAmplitude)))
            {
                throw OutOfRangeValue();
            }
            unsigned short shVal = static_cast<unsigned short>(val);
            if (signal->getFormat().byteOrder() == QAudioFormat::LittleEndian)
            {
                unsigned short tmp = qToLittleEndian(shVal);
                char* pTmp = reinterpret_cast<char*>(&tmp);
                sampleData[0] = pTmp[0];
                sampleData[1] = pTmp[1];
            }
            else
            {
                unsigned short tmp = qToBigEndian(shVal);
                char* pTmp = reinterpret_cast<char*>(&tmp);
                sampleData[0] = pTmp[0];
                sampleData[1] = pTmp[1];
            }
        }
    }
    else
    {
        throw Signal::SampleSizeUnset();
    }
}

Sample::Sample(char *_sampleData, const Signal* const _signal):
    sampleData(_sampleData),
    constSampleData(_sampleData),
    signal(_signal)
{}

Sample::Sample(const char *_constSampleData, const Signal* const _signal):
    sampleData(NULL),
    constSampleData(_constSampleData),
    signal(_signal)
{}
