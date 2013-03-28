#include "soundRecorder.h"

SoundRecorder::SoundRecorder(QAudioDeviceInfo& device):
    audioDevice(device),
    currentFramePos(0)
{
    defaultFormatSettings();
    audioIn = new QAudioInput(device, audioFormat, this);
    audioIn->setNotifyInterval(SoundRecorder::frameLength);
    byteArray = new QByteArray();
    buffer = new QBuffer(byteArray, this);
}
SoundRecorder::~SoundRecorder()
{
    delete byteArray;
}

void SoundRecorder::startRecording()
{
    buffer->open(QIODevice::WriteOnly);
    connect(audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
    audioIn->start(buffer);
}
void SoundRecorder::stopRecording()
{
    cout << "total: " << buffer->size() << " bytes were recorded" << endl;
    audioIn->stop();
}

void SoundRecorder::recordFrame()
{
    qint64 expectedBytesInFrame = SoundRecorder::frameLength
            * audioFormat.frequency() * audioFormat.channelCount() * audioFormat.sampleSize() / 8;
    qint64 actualBytesInFrame = buffer->pos() - currentFramePos;
    qint64 bytesInFrame = qMin(expectedBytesInFrame, actualBytesInFrame);

    QByteArray frameBytes = QByteArray::fromRawData(byteArray->constData() + currentFramePos, bytesInFrame);
    currentFramePos += bytesInFrame;
    emit frameRecorded(frameBytes);
}

void SoundRecorder::defaultFormatSettings()
{
    audioFormat.setFrequency(8000);
    audioFormat.setChannels(1);
    audioFormat.setSampleSize(8);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
}
