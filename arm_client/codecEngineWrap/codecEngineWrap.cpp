#include <cstring>

#include "codecEngineWrap.h"

const QString CodecEngineWrap::serverName = "dsp-server";

CodecEngineWrap::CodecEngineWrap(bool verbose):
    engineHandle(NULL)
{
    CERuntime_init();

    /*
    if (verbose)
    {
      Diags_setMask("xdc.runtime.Main+EX1234567");
      Diags_setMask(Engine_MODNAME"+EX1234567");
    }
    */
}

CodecEngineWrap::~CodecEngineWrap()
{
    CERuntime_exit();
}

void CodecEngineWrap::open(const QString &serverPath) throw(OpenExc)
{
    // заполняем описание энжена
    Engine_Desc desc;
    Engine_initDesc(&desc);
    desc.name = serverName.toAscii().data();
    desc.remoteName = serverPath.toAscii().data();

    int addRes = Engine_add(&desc);
    if (addRes != Engine_EOK)
    {
        if (addRes == Engine_EINUSE)
            throw OpenExc(addRes, "The Engine name is non-NULL, and the Engine is open");
        else if (addRes == Engine_EINVAL)
            throw OpenExc(addRes, "Bad paramater passed to method");
        else if (addRes == Engine_EEXIST)
            throw OpenExc(addRes, "There is no engine with the given name");
        else if (addRes == Engine_EINUSE)
            throw OpenExc(addRes, "The name of the alg in algorythm description (name) is already in use");
        else
            throw OpenExc(addRes, "Unknow error");
    }

    int eoErr = 0;
    engineHandle = Engine_open(serverName.toAscii().data(), NULL, &eoErr);
    if (engineHandle == NULL)
    {
        if (eoErr == Engine_EEXIST)
            throw OpenExc(eoErr, "Name (of engine) does not exist");
        else if (eoErr == Engine_ENOMEM)
            throw OpenExc(eoErr, "Can't allocate memory");
        else if (eoErr == Engine_EDSPLOAD)
            throw OpenExc(eoErr, "Can't load the DSP");
        else if (eoErr == Engine_ENOCOMM)
            throw OpenExc(eoErr, "Can't create a comm connection to DSP");
        else if (eoErr == Engine_ENOSERVER)
            throw OpenExc(eoErr, "Can't locate the server on the DSP");
        else if (eoErr == Engine_ECOMALLOC)
            throw OpenExc(eoErr, "Can't allocate communication buffer");
        else
            throw OpenExc(eoErr, "Unknow error");
    }
}

void CodecEngineWrap::close()
{
    if (engineHandle == NULL)
      return;
    Engine_close(engineHandle);
    engineHandle = NULL;
}

void CodecEngineWrap::create(QString algName,
                             size_t maxSrcWidth, size_t maxSrcHeight,
                             //size_t srcLineLength, size_t _srcImageSize, uint32_t _srcFormat,
                             size_t maxDstWidth, size_t maxDstHeight,
                             //size_t _dstLineLength, size_t _dstImageSize, uint32_t _dstFormat
                             )
{
    VIDTRANSCODE_Params params;
    params.size = sizeof(params);
    params.numOutputStreams = 1;
    params.formatInput = do_convertPixelFormat(_ce, _srcFormat);
    params.formatOutput[0] = do_convertPixelFormat(_ce, _dstFormat);
    params.maxHeightInput = maxSrcHeight;
    params.maxWidthInput = maxSrcWidth;
    params.maxHeightOutput[0] = maxDstHeight;
    params.maxWidthOutput[0] = maxDstWidth;

    vidtranscodeHandle = VIDTRANSCODE_create(engineHandle, algName.toAscii().data(), &params);
    if (vidtranscodeHandle == NULL)
    {
        throw CreateExc();
    }
}

void CodecEngineWrap::memoryAlloc(size_t _srcBuffSize, size_t _dstBuffSize)
{
    memset(allocParams, 0, sizeof(allocParams));
    allocParams.type = Memory_CONTIGPOOL;
    #warning TODO check - maybe Memory_CACHED?
    allocParams.flags = Memory_NONCACHED;
    allocParams.align = BUFALIGN;
    allocParams.seg = 0;

    srcBuffSize = ALIGN_UP(_srcBuffSize, BUFALIGN);
    srcBuff = Memory_alloc(srcBuffSize, allocParams);
    if (srcBuff == NULL)
    {
        throw MemoryAllocExc();
    }

    dstBuffSize = ALIGN_UP(_dstBuffSize, BUFALIGN);
    dstBuff = Memory_alloc(dstBuffSize, allocParams);
    if (dstBuff == NULL)
    {
        memoryFree();
        throw MemoryAllocExc();
    }

    return 0;
}

void CodecEngineWrap::memoryFree()
{
    if (srcBuff != NULL)
    {
      Memory_free(srcBuff, srcBuffSize, allocParams);
      srcBuff = NULL;
      srcBuffSize = 0;
    }

    if (dstBuff != NULL)
    {
      Memory_free(dstBuff, dstBuffSize, allocParams);
      dstBuff = NULL;
      dstBuffSize = 0;
    }
}

