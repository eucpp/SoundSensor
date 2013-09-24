#include "soundRecorder.h"

SoundRecorder::SoundRecorder():
    audioDevice(QAudioDeviceInfo::defaultInputDevice()),
    audioIn(new QAudioInput(audioDevice, SoundRecorder::defaultAudioFormat())),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn->setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(audioIn.data(), SIGNAL(notify()), this, SLOT(recordFrame()));

    connect(&buffer, SIGNAL(bytesWritten(qint64)), this, SLOT(testBytesWritten(qint64)));
    connect(&buffer, SIGNAL(readyRead()), this, SLOT(testReadyRead()));
}

SoundRecorder::SoundRecorder(const QAudioDeviceInfo& device):
    audioDevice(device),
    audioIn(new QAudioInput(audioDevice, SoundRecorder::defaultAudioFormat())),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn->setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(audioIn.data(), SIGNAL(notify()), this, SLOT(recordFrame()));

    connect(&buffer, SIGNAL(bytesWritten(qint64)), this, SLOT(testBytesWritten(qint64)));
    connect(&buffer, SIGNAL(readyRead()), this, SLOT(testReadyRead()));
}

SoundRecorder::SoundRecorder(const QAudioFormat& format):
    audioDevice(QAudioDeviceInfo::defaultInputDevice()),
    audioIn(new QAudioInput(audioDevice, format)),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn->setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(audioIn.data(), SIGNAL(notify()), this, SLOT(recordFrame()));

    connect(&buffer, SIGNAL(bytesWritten(qint64)), this, SLOT(testBytesWritten(qint64)));
    connect(&buffer, SIGNAL(readyRead()), this, SLOT(testReadyRead()));
}

SoundRecorder::SoundRecorder(const QAudioDeviceInfo& device, const QAudioFormat& format):
    audioDevice(device),
    audioIn(new QAudioInput(audioDevice, format)),
    currentFramePos(0),
    buffer(&byteArray)
{
    audioIn->setNotifyInterval(SoundRecorder::defaultFrameLength);
    connect(audioIn.data(), SIGNAL(notify()), this, SLOT(recordFrame()));

    connect(&buffer, SIGNAL(bytesWritten(qint64)), this, SLOT(testBytesWritten(qint64)));
    connect(&buffer, SIGNAL(readyRead()), this, SLOT(testReadyRead()));
}

Signal SoundRecorder::getSignal() const
{
    if (audioIn->state() == QAudio::IdleState)
        return Signal(0, audioIn->format());
    if (audioIn->state() == QAudio::ActiveState)
        return Signal(QByteArray::fromRawData(byteArray.constData(), buffer.pos()), getFormat());
    return Signal(byteArray, getFormat());
}

QAudioFormat SoundRecorder::getFormat() const
{
    return audioIn->format();
}

void SoundRecorder::setFormat(const QAudioFormat& format)
{
    audioIn->stop();
    int frameLength = audioIn->notifyInterval();
    audioIn.reset(new QAudioInput(audioDevice, format));
    audioIn->setNotifyInterval(frameLength);
    connect(audioIn.data(), SIGNAL(notify()), this, SLOT(recordFrame()));
}

QAudioDeviceInfo SoundRecorder::getDevice() const
{
    return audioDevice;
}

void SoundRecorder::setDevice(const QAudioDeviceInfo& device)
{
    audioIn->stop();
    QAudioFormat format = audioIn->format();
    int frameLength = audioIn->notifyInterval();
    audioIn.reset(new QAudioInput(device, format));
    audioIn->setNotifyInterval(frameLength);
    connect(audioIn.data(), SIGNAL(notify()), this, SLOT(recordFrame()));
}


void SoundRecorder::setFrameLength(int length)
{
    audioIn->setNotifyInterval(length);
}

int SoundRecorder::getFrameLength() const
{
    return audioIn->notifyInterval();
}

QAudioFormat SoundRecorder::defaultAudioFormat()
{
    QAudioFormat format;
    format.setSampleRate(44100);
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
    audioIn->start(&buffer);
}

void SoundRecorder::stop()
{
    audioIn->stop();
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

