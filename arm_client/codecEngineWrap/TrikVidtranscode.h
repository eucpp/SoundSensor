#ifndef TRIKVIDTRANSCODE_H
#define TRIKVIDTRANSCODE_H

#include <QString>

#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/vidtranscode/vidtranscode.h>

#include "CodecEngineWrap.h"
#include "CodecEngineExceptions.h"

class TrikVidtranscode
{
public:
    /**
      *
      */
    TrikVidtranscode(const CodecEngineWrap& engine,
                     size_t maxSrcWidth, size_t maxSrcHeight,
                     uint32_t _srcFormat,
                     size_t maxDstWidth, size_t maxDstHeight,
                     uint32_t _dstFormat);
    /**
      *
      */
    ~TrikVidtranscode();
    /**
      *
      */
    void control(size_t _dstWidth, size_t _dstHeight);
    /**
      *
      * @return Количество заполненных байт в выходном буфере (_dstFrameUsed)
      */
    size_t process(const void* _srcFramePtr, size_t _srcFrameSize,
                 void* _dstFramePtr, size_t _dstFrameSize);

private:
    static const QString algName;

    void memoryAlloc(size_t _srcBuffSize, size_t _dstBuffSize);
    void memoryFree();

    XDAS_Int32 convertPixelFormat(uint32_t _format);

    Engine_Handle engineHandle;
    VIDTRANSCODE_Handle vidtranscodeHandle;
    Memory_AllocParams allocParams;
    void* srcBuff;
    size_t srcBuffSize;
    void* dstBuff;
    size_t dstBuffSize;
};

#endif // TRIKVIDTRANSCODE_H
