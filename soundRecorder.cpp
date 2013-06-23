#include "soundRecorder.h"

SoundRecorder::SoundRecorder():
    audioDevice(QAudioDeviceInfo::defaultInputDevice()),
    audioIn(audioDevice, SoundRecorder::defaultAudioFormat()),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
}
SoundRecorder::SoundRecorder(const QAudioDeviceInfo& device):
    audioDevice(device),
    audioIn(audioDevice, SoundRecorder::defaultAudioFormat()),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
}
SoundRecorder::SoundRecorder(const QAudioFormat& format):
    audioDevice(QAudioDeviceInfo::defaultInputDevice()),
    audioIn(audioDevice, format),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
}
SoundRecorder::SoundRecorder(const QAudioDeviceInfo& device, const QAudioFormat& format):
    audioDevice(device),
    audioIn(audioDevice, format),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn.setNotifyInterval(SoundRecorder::defaultFrameLength);
}

Signal SoundRecorder::getSignal() const
{
    if (audioIn.state() == QAudio::ActiveState)
        return Signal(QByteArray::fromRawData(byteArray.constData(), buffer.pos()), getAudioFormat());
    return Signal(byteArray, getAudioFormat());
}


void SoundRecorder::startRecording()
{
    buffer.open(QIODevice::WriteOnly);
    connect(&audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
    audioIn.start(&buffer);
}

void SoundRecorder::stopRecording()
{
    audioIn.stop();
    emit recordingStopped(getSignal());
}

void SoundRecorder::recordFrame()
{
    qint64 bytesInFrame = buffer.pos() - currentFramePos;
    Signal signal(QByteArray::fromRawData(byteArray.constData() + currentFramePos, bytesInFrame),
                  getAudioFormat());
    currentFramePos += bytesInFrame;
    emit frameRecorded(signal);
}

QAudioFormat inline SoundRecorder::getAudioFormat() const
{
    return audioIn.format();
}

QAudioDeviceInfo inline SoundRecorder::getAudioDevice() const
{
    return audioDevice;
}

void inline SoundRecorder::setFrameLength(int length)
{
    audioIn.setNotifyInterval(length);
}

int inline SoundRecorder::getFrameLength() const
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
