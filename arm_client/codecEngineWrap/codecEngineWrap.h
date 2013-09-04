#ifndef CODECENGINEWRAP_H
#define CODECENGINEWRAP_H

#include <QString>

#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/osal/Memory.h>

#include <ti/sdo/ce/vidtranscode/vidtranscode.h>

class CodecEngineWrap
{
public:
    /**
      *
      */
    class OpenExc
    {
    public:
        OpenExc(int _code, const QString& _msg):
            code(_code),
            msg(_msg)
        {}
        const int code;
        const QString msg;
    };
    /**
      *
      */
    class MemoryAllocExc {};
    /**
      *
      */
    class CreateExc {};

    /**
      * Конструктор выполняет инициализацию (CERuntime_init())
      */
    CodecEngineWrap(bool verbose = false);
    /**
      *
      */
    ~CodecEngineWrap();
    /**
      *
      */
    void open(const QString& serverPath) throw(OpenExc);
    /**
      *
      */
    void close();
    /**
      *
      */
    void create(QString algName, VIDTRANSCODE_Params params);

private:
    void memoryAlloc(size_t _srcBuffSize, size_t _dstBuffSize);
    void memoryFree();

    Engine_Handle engineHandle;
    VIDTRANSCODE_Handle vidtranscodeHandle;

    //typedef ti_sdo_ce_osal_Memory_AllocParams Osal_Memeory_AllocParams;
    Memory_AllocParams allocParams;
    void* srcBuff;
    size_t srcBuffSize;
    void* dstBuff;
    size_t dstBuffSize;

    static const QString serverName;
};

#endif // CODECENGINEWRAP_H
