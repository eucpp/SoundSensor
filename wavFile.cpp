#include "wavFile.h"

WavFile::WavFile():
    file(),
    openmode(NotOpen),
    headerSetFlag(false)
{}
WavFile::WavFile(const QString &filename):
    file(filename),
    openmode(NotOpen),
    headerSetFlag(false)
{}

void WavFile::open(OpenModes mode)
{
    open(mode, QAudioFormat());
}

void WavFile::open(OpenModes mode, const QAudioFormat& format)
{
    try
    {
        openmode = mode;
        if (openmode == ReadOnly)
        {
            if (!file.open(QIODevice::ReadOnly))
                throw OpenFileExc();
            // проверяем размер заголовка файла
            if (file.size() > 0 && file.size() < 44)
                throw OpenFileExc();
            seek(0);
            header = readHeader();
            headerSetFlag = true;
            return;
        }
        else if (openmode == WriteOnly)
        {
            if (!file.open(QIODevice::WriteOnly))
                throw OpenFileExc();
            if (isCorrectFormat(format))
            {
                header = format;
                writeHeader(header);
                headerSetFlag = true;
            }
            seek(0);
            return;
        }
        else if (openmode == Append)
        {
            // сначала открываем на чтение, чтобы проситать заголовок.
            if (!file.open(QIODevice::ReadOnly))
                throw OpenFileExc();
            // проверяем размер заголовка файла
            if (file.size() > 0 && file.size() < 44)
                throw OpenFileExc();
            header = readHeader();
            headerSetFlag = true;
            file.close();
            if (!file.open(QIODevice::Append))
                throw OpenFileExc();
            seek(size());
            return;
        }
    }
    catch (UncorrectHeader exc)
    {
        throw OpenFileExc();
    }

    /*
    else if (openmode == ReadWrite)
    {
        if (!file.open(QIODevice::ReadWrite))
            throw OpenFileExc();
        // проверяем размер заголовка файла
        if (file.size() > 0 && file.size() < 44)
            throw OpenFileExc();
        header = readHeader();
        // перекодируем содержимое файла, если был передан новый формат, и он отличается от старого
        if (isCorrectFormat(format) && header != format)
        {
            Signal fileData = readAll();
            writeHeader(format);
            header = format;
            seek(0);
            write(fileData);
            seek(size());
        }
        return;
    }
    */
}
void WavFile::close()
{
    file.close();
    openmode = NotOpen;
    headerSetFlag = false;
}

void WavFile::setFileName(const QString &filename)
{
    if (openmode != NotOpen)
        file.close();
    file.setFileName(filename);
}

QString WavFile::fileName() const
{
    return file.fileName();
}

bool WavFile::headerSet() const
{
    return headerSetFlag;
}

void WavFile::setHeader(const QAudioFormat &format) throw(WriteDisabledExc)
{
    if ((openmode == ReadOnly) || (openmode == WriteOnly))
        throw WriteDisabledExc();
    else if (!headerSetFlag)
    {
        header = format;
        writeHeader(header);
    }
    else if (header != format)
    {
        int currPos = pos();
        Signal fileData = readAll();
        writeHeader(format);
        header = format;
        seek(0);
        write(fileData);
        seek(currPos);
    }
}

QAudioFormat WavFile::getHeader() const
{
    if (headerSetFlag)
        return header;
    else
        return QAudioFormat();
}

bool WavFile::isOpen() const
{
    return file.isOpen();
}

bool WavFile::seek(int pos)
{
    return file.seek(pos + 44);
}

int WavFile::pos()
{
    return file.pos() - 44;
}

int WavFile::size()
{
    if (openmode == NotOpen)
        return 0;
    return file.size() - 44;
}

Signal WavFile::read(int length) throw(ReadDisabledExc)
{
    if (openmode == NotOpen)
        return Signal();
    if (openmode == WriteOnly)
        throw ReadDisabledExc();
    int bytesNum = length * header.sampleSize() / 8;
    QByteArray bytes = file.read(bytesNum);
    return Signal(bytes, header);
}

Signal WavFile::readAll() throw(ReadDisabledExc)
{
    if (openmode == NotOpen)
        return Signal();
    if (openmode == WriteOnly)
        throw ReadDisabledExc();
    int currPos = pos();
    seek(0);
    QByteArray bytes = file.readAll();
    seek(currPos);
    return Signal(bytes, header);
}

int WavFile::write(Signal signal, int length) throw(WriteDisabledExc)
{
    if ((openmode == NotOpen) || !headerSetFlag)
        return 0;
    if (openmode == ReadOnly)
        throw WriteDisabledExc();
    QByteArray bytes = signal.subSignal(0, length).toByteArray(header);
    int n = file.write(bytes);
    setDataSize(size());
    return n / (header.sampleSize() / 8);
}


QAudioFormat WavFile::readHeader()
{
    qint64 currPos = pos();
    file.seek(0);
    QByteArray headerArrayBytes = file.read(sizeof(Header));
    const char* headerBytes = headerArrayBytes.constData();
    seek(currPos);

    const Header* pHeader = reinterpret_cast<const Header*>(headerBytes);
    // проверяем, что это действительно заголовок wav файла
    if (    (pHeader->chunkId[0] != 'R') ||
            (pHeader->chunkId[1] != 'I') ||
            (pHeader->chunkId[2] != 'F') ||
            (pHeader->chunkId[3] != 'F'))
        throw UncorrectHeader();
    if (    (pHeader->format[0] != 'W') ||
            (pHeader->format[1] != 'A') ||
            (pHeader->format[2] != 'V') ||
            (pHeader->format[3] != 'E'))
        throw UncorrectHeader();
    if (    (pHeader->subchunk1Id[0] != 'f') ||
            (pHeader->subchunk1Id[1] != 'm') ||
            (pHeader->subchunk1Id[2] != 't') ||
            (pHeader->subchunk1Id[3] != ' '))
        throw UncorrectHeader();


    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setSampleRate(pHeader->sampleRate);
    format.setChannels(pHeader->numChannels);
    format.setSampleSize(pHeader->bitsPerSample);
    if (pHeader->bitsPerSample == 8)
        format.setSampleType(QAudioFormat::UnSignedInt);
    else
        format.setSampleType(QAudioFormat::SignedInt);
    return format;
}

void WavFile::writeHeader(const QAudioFormat& format)
{
    Header header;
    header.chunkId[0]='R';
    header.chunkId[1]='I';
    header.chunkId[2]='F';
    header.chunkId[3]='F';

    header.chunkSize = 36;

    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';

    header.subchunk1Id[0] = 'f';
    header.subchunk1Id[1] = 'm';
    header.subchunk1Id[2] = 't';
    header.subchunk1Id[3] = ' ';

    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = format.channels();
    header.sampleRate = format.sampleRate();
    header.byteRate = header.sampleRate * header.numChannels * format.sampleSize() / 8;
    header.blockAlign = header.numChannels * format.sampleSize() / 8;
    header.bitsPerSample = format.sampleSize();

    header.subchunk2Id[0] = 'd';
    header.subchunk2Id[1] = 'a';
    header.subchunk2Id[2] = 't';
    header.subchunk2Id[3] = 'a';

    header.subchunk2Size = 0;

    char* bytes = reinterpret_cast<char*>(&header);
    qint64 currPos = pos();
    file.seek(0);
    file.write(bytes, sizeof(Header));
    seek(currPos);
}

void WavFile::setDataSize(int size)
{
    int currPos = pos();
    if (openmode == Append)
    {
        file.close();
        file.open(QIODevice::ReadWrite);
    }
    file.seek(40);
    file.write(reinterpret_cast<char*>(&size), 4);
    if (openmode == Append)
    {
        file.close();
        file.open(QIODevice::Append);
    }
    seek(currPos);
}

bool WavFile::isCorrectFormat(const QAudioFormat &format)
{
    return !((format.sampleRate() == -1) || (format.sampleSize() == -1) || (format.channelCount() == -1));
}

/*
unsigned int WavFile::readDataSize()
{
    unsigned int currPos = pos();
    file.seek(40);
    char* charSize = new char[5];
    file.read(charSize, 4);
    charSize[4] = '\0';
    seek(currPos);
    unsigned int* pSize = reinterpret_cast<unsigned int*>(charSize);
    unsigned int size = *pSize;
    delete[] charSize;
    return size;
}
*/
