#include "soundRecorder.h"

SoundRecorder::SoundRecorder():
    audioDevice(QAudioDeviceInfo::defaultInputDevice()),
    audioIn(audioDevice, SoundRecorder::defaultAudioFormat()),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(&audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
}

SoundRecorder::SoundRecorder(const QAudioDeviceInfo& device):
    audioDevice(device),
    audioIn(audioDevice, SoundRecorder::defaultAudioFormat()),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(&audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
}

SoundRecorder::SoundRecorder(const QAudioFormat& format):
    audioDevice(QAudioDeviceInfo::defaultInputDevice()),
    audioIn(audioDevice, format),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(&audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
}

SoundRecorder::SoundRecorder(const QAudioDeviceInfo& device, const QAudioFormat& format):
    audioDevice(device),
    audioIn(audioDevice, format),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(&audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
}

Signal SoundRecorder::getSignal() const
{
    if (audioIn.state() == QAudio::ActiveState)
        return Signal(QByteArray::fromRawData(byteArray.constData(), buffer.pos()), getFormat());
    return Signal(byteArray, getFormat());
}

QAudioFormat SoundRecorder::getFormat() const
{
    return audioIn.format();
}

QAudioDeviceInfo SoundRecorder::getDevice() const
{
    return audioDevice;
}

void SoundRecorder::setFrameLength(int length)
{
    audioIn.setNotifyInterval(length);
}

int SoundRecorder::getFrameLength() const
{
    return audioIn.notifyInterval();
}

QAudioFormat SoundRecorder::defaultAudioFormat()
{
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannels(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    return format;
}

void SoundRecorder::start()
{
    buffer.open(QIODevice::WriteOnly);
    audioIn.start(&buffer);
}

void SoundRecorder::stop()
{
    audioIn.stop();
    buffer.close();
    emit recordingStopped(getSignal());
}

void SoundRecorder::recordFrame()
{
    qint64 bytesInFrame = buffer.pos() - currentFramePos;
    Signal signal(QByteArray::fromRawData(byteArray.constData() + currentFramePos, bytesInFrame), getFormat());
    currentFramePos += bytesInFrame;
    emit frameRecorded(signal);
}

