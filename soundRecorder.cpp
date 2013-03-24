#include "soundRecorder.h"

SoundRecorder::SoundRecorder()
{
    audioFormat = new QAudioFormat;
    defaultFormatSettings();
    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    audioIn = new QAudioInput(device, *audioFormat);
    byteArray = new QByteArray;
    buffer = new QBuffer(byteArray);
}
SoundRecorder::~SoundRecorder()
{
    delete audioFormat;
    delete audioIn;
    delete byteArray;
    delete buffer;
}

void SoundRecorder::record()
{

    //connect(buffer, SIGNAL(readyRead()), this, SLOT(testDataReady()));
    //connect(buffer, SIGNAL(bytesWritten(qint64)), this, SLOT(testBytesWritten(qint64)));
    buffer->open(QIODevice::ReadWrite);
    cout << buffer->isReadable() << endl;
    cout << buffer->isWritable() << endl;
    cout << buffer->isSequential() << endl;
    cout << buffer->bytesToWrite() << endl;
    audioIn->start(buffer);
}
void SoundRecorder::defaultFormatSettings()
{
    audioFormat->setFrequency(8000);
    audioFormat->setChannels(1);
    audioFormat->setSampleSize(8);
    audioFormat->setCodec("audio/pcm");
    audioFormat->setByteOrder(QAudioFormat::LittleEndian);
    audioFormat->setSampleType(QAudioFormat::UnSignedInt);
}

void SoundRecorder::testBytesWritten(qint64 size)
{
    cout << "written " << size << endl;
    //qDebug("written %d",size);
}
void SoundRecorder::testDataReady()
{

    int blockSize = buffer->size(); // returns always zero when using IODevice
    cout << blockSize << " bytes ready" << endl;
    //qDebug("%d bytes ready", blockSize);
    if (blockSize <= 0)
        return;
    QByteArray ba;
// 1 Try directly
    ba = buffer->read(blockSize); // <-- not working (ba is empty)
    cout << "buffer size " << ba.size() << endl;
    //qDebug(" ba size %d",ba.size() );
}
void SoundRecorder::stop()
{
    audioIn->stop();
}

void SoundRecorder::testplay()
{
    stop();
    cout << audioIn->error() << endl;
    cout << "play" << endl;
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(*audioFormat)) {
        cout << "raw audio format not supported by backend, cannot play audio.";
        return;
    }
    cout << buffer->bytesToWrite() << endl;
    cout << buffer->size() << endl;

    QAudioOutput* out = new QAudioOutput(*audioFormat);
    buffer->seek(0);
    out->start(buffer);
}
