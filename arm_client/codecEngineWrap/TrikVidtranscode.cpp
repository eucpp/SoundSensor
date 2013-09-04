#include "TrikVidtranscode.h"

using namespace CodecEngineExceptions;

const QString TrikVidtranscode::algName = "vidtranscode_resample";

TrikVidtranscode::TrikVidtranscode(const CodecEngineWrap& engine,
                                   size_t maxSrcWidth, size_t maxSrcHeight,
                                   size_t _srcImageSize, uint32_t _srcFormat,
                                   size_t maxDstWidth, size_t maxDstHeight,
                                   size_t _dstImageSize, uint32_t _dstFormat)
{
    engineHandle = engine.getEngineHandle();
    VIDTRANSCODE_Params params;
    params.size = sizeof(params);
    params.numOutputStreams = 1;
    params.formatInput = convertPixelFormat(_srcFormat);
    params.formatOutput[0] = convertPixelFormat(_dstFormat);
    params.maxHeightInput = maxSrcHeight;
    params.maxWidthInput = maxSrcWidth;
    params.maxHeightOutput[0] = maxDstHeight;
    params.maxWidthOutput[0] = maxDstWidth;

    vidtranscodeHandle = VIDTRANSCODE_create(engineHandle, algName.toAscii().data(), &params);
    if (vidtranscodeHandle == NULL)
    {
        throw CreateExc();
    }

    memoryAlloc(_srcImageSize, _dstImageSize);
}

TrikVidtranscode::~TrikVidtranscode()
{
    Engine_close(engineHandle);
    memoryFree();
}

void TrikVidtranscode::control(size_t _dstWidth, size_t _dstHeight)
{
    IVIDTRANSCODE_DynamicParams params;
    params.keepInputResolutionFlag[0] = XDAS_FALSE;
    params.outputHeight[0] = _dstHeight;
    params.outputWidth[0] = _dstWidth;
    params.keepInputFrameRateFlag[0] = XDAS_TRUE;
    /*
    ceDynamicParams.inputHeight = _srcHeight;
    ceDynamicParams.inputWidth = _srcWidth;
    ceDynamicParams.inputLineLength = _srcLineLength;
    ceDynamicParams.outputLineLength[0] = _dstLineLength;
    */

    IVIDTRANSCODE_Status status;
    memset(&status, 0, sizeof(status));
    status.size = sizeof(status);
    XDAS_Int32 controlResult = VIDTRANSCODE_control(vidtranscodeHandle, XDM_SETPARAMS, &params, &status);
    if (controlResult != IVIDTRANSCODE_EOK)
    {
        throw ConstrolExc();
    }
}

using namespace CodecEngineExceptions::ProcessExc;

size_t TrikVidtranscode::process(const void *_srcFramePtr, size_t _srcFrameSize,
                              void *_dstFramePtr, size_t _dstFrameSize)
{
    if (srcBuff == NULL || dstBuff == NULL)
    {
        throw ProcessExc(MEMORY_NOT_ALLOCATED, "Memory not allocated. Check is ... was called");
    }
    if (_srcFramePtr == NULL || _dstFramePtr == NULL)
    {
        throw ProcessExc(INVALID_INPUT_ARGUMENTS, "_srvFramePtr and _dstFramePtr must be not NULL");
    }
    if (_srcFrameSize > srcBuffSize || _dstFrameSize > dstBuffSize)
    {
        throw ProcessExc(INVALID_INPUT_ARGUMENTS, "_srcFrameSize or _dstFrameSize too large");
    }

    VIDTRANSCODE_InArgs tcInArgs;
    memset(&tcInArgs, 0, sizeof(tcInArgs));
    tcInArgs.size = sizeof(tcInArgs);
    tcInArgs.numBytes = _srcFrameSize;
    tcInArgs.inputID = 0;

    VIDTRANSCODE_OutArgs tcOutArgs;
    memset(&tcOutArgs,    0, sizeof(tcOutArgs));
    tcOutArgs.size = sizeof(tcOutArgs);

    XDM1_BufDesc tcInBufDesc;
    memset(&tcInBufDesc,  0, sizeof(tcInBufDesc));
    tcInBufDesc.numBufs = 1;
    tcInBufDesc.descs[0].buf = srcBuff;
    tcInBufDesc.descs[0].bufSize = _srcFrameSize;

    XDM_BufDesc tcOutBufDesc;
    memset(&tcOutBufDesc, 0, sizeof(tcOutBufDesc));
    XDAS_Int8* tcOutBufDesc_bufs[1];
    XDAS_Int32 tcOutBufDesc_bufSizes[1];
    tcOutBufDesc.numBufs = 1;
    tcOutBufDesc.bufs = tcOutBufDesc_bufs;
    tcOutBufDesc.bufs[0] = dstBuff;
    tcOutBufDesc.bufSizes = tcOutBufDesc_bufSizes;
    tcOutBufDesc.bufSizes[0] = _dstFrameSize;

    memcpy(srcBuff, _srcFramePtr, _srcFrameSize);

    // invalidate *whole* cache, not only written portion, just in case
    Memory_cacheWbInv(srcBuff, srcBuffSize);
    // invalidate *whole* cache, not only expected portion, just in case
    Memory_cacheInv(dstBuff, dstBuffSize);

    XDAS_Int32 res = VIDTRANSCODE_process(vidtranscodeHandle, &tcInBufDesc, &tcOutBufDesc, &tcInArgs, &tcOutArgs);

    //fprintf(stderr, "VIDTRANSCODE_process result %d \n", processResult);

    if (res != IVIDTRANSCODE_EOK)
    {
      throw ProcessExc(DSP_SERVER_ERROR,
                       QString("VIDTRANSCODE_process extended error: ") + QString.setNum(tcOutArgs.extendedError));
    }

    if (XDM_ISACCESSMODE_WRITE(tcOutArgs.encodedBuf[0].accessMask))
    {
        // write-back *whole* cache, not only modified portion, just in case
        Memory_cacheWb(_ce->m_dstBuffer, _ce->m_dstBufferSize);
    }

    if (tcOutArgs.encodedBuf[0].bufSize > _dstFrameSize)
    {
        throw ProcessExc(INVALID_OUTPUT_ARGUMENTS, "VIDTRANSCODE_process returned too large buffer");
    }
    else if (tcOutArgs.encodedBuf[0].bufSize < 0)
    {
        throw ProcessExc(INVALID_OUTPUT_ARGUMENTS, "VIDTRANSCODE_process returned negative buffer size");
    }

    size_t frameUsed = tcOutArgs.encodedBuf[0].bufSize;
    memcpy(_dstFramePtr, dstBuff, frameUsed);

    return frameUsed;
}

void TrikVidtranscode::memoryAlloc(size_t _srcBuffSize, size_t _dstBuffSize)
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

void TrikVidtranscode::memoryFree()
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

#warning TO DO delete this and include trik_vidtranscode_resample.h
typedef enum TRIK_VIDTRANSCODE_RESAMPLE_VideoFormat
{
  TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_UNKNOWN = 0,
  TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_RGB888 = XDM_CUSTOMENUMBASE,
  TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_RGB565,
  TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_RGB565X,
  TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_YUV444,
  TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_YUV422
} TRIK_VIDTRANSCODE_RESAMPLE_VideoFormat;


XDAS_Int32 TrikVidtranscode::convertPixelFormat(uint32_t _format)
{
    switch (_format)
    {
        case V4L2_PIX_FMT_RGB24:	return TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_RGB888;
        case V4L2_PIX_FMT_RGB565:	return TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_RGB565;
        case V4L2_PIX_FMT_RGB565X:	return TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_RGB565X;
        case V4L2_PIX_FMT_YUV32:	return TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_YUV444;
        case V4L2_PIX_FMT_YUYV:	return TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_YUV422;
        default:
        fprintf(stderr, "Unknown pixel format %c%c%c%c\n",
              _format&0xff, (_format>>8)&0xff, (_format>>16)&0xff, (_format>>24)&0xff);
        return TRIK_VIDTRANSCODE_RESAMPLE_VIDEO_FORMAT_UNKNOWN;
    }
}
