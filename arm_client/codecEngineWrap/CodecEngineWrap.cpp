#include <cstring>

#include "CodecEngineWrap.h"

const QString CodecEngineWrap::serverName = "dsp-server";

using namespace CodecEngineExceptions;

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

bool CodecEngineWrap::isOpen() const
{
    return (engineHandle != NULL);
}

Engine_Handle CodecEngineWrap::getEngineHandle() const
{
    if (!isOpen())
    {
        throw EngineNotOpened;
    }
    return engineHandle;
}


