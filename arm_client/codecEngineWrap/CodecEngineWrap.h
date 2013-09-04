#ifndef CODECENGINEWRAP_H
#define CODECENGINEWRAP_H

#include <QString>

#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include "CodecEngineExceptions.h"

class CodecEngineWrap
{
public:
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
    void open(const QString& serverPath) throw(CodecEngineExceptions::OpenExc);
    /**
      *
      */
    bool isOpen() const;
    /**
      *
      */
    Engine_Handle getEngineHandle() const throw(CodecEngineExceptions::EngineNotOpened);
private:
    Engine_Handle engineHandle;

    //typedef ti_sdo_ce_osal_Memory_AllocParams Osal_Memeory_AllocParams;


    static const QString serverName;
};

#endif // CODECENGINEWRAP_H
