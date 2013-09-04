#ifndef CODECENGINEEXCEPTIONS_H
#define CODECENGINEEXCEPTIONS_H

#include <QString>

namespace CodecEngineExceptions
{
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
    class EngineNotOpened {};
    /**
      *
      */
    class MemoryAllocExc {};
    /**
      *
      */
    class CreateExc {};
    /**
      *
      */
    class ConstrolExc {};
    /**
      *
      */
    class ProcessExc
    {
    public:
        enum ErrorCode
        {
            MEMORY_NOT_ALLOCATED,
            INVALID_INPUT_ARGUMENTS,
            INVALID_OUTPUT_ARGUMENTS,
            DSP_SERVER_ERROR
        };
        ProcessExc(ErrorCode _code, const QString& _msg):
            code(_code),
            msg(_msg)
        {}
        const ErrorCode code;
        const QString msg;
    };
}

#endif // CODECENGINEEXCEPTIONS_H
