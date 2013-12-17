trik {
    HEADERS += \
        codecEngineWrap/CodecEngineExceptions.h \
        codecEngineWrap/TrikVidtranscode.h

    SOURCES += \
        codecEngineWrap/TrikVidtranscode.cpp
}

SOURCES += \
    codecEngineWrap/codecEngine.cpp \
    codecEngineWrap/denoiser.cpp \
    codecEngineWrap/trikognitionCE.cpp

HEADERS += \
    codecEngineWrap/codecEngine.h \
    codecEngineWrap/denoiser.h \
    codecEngineWrap/trikognitionCE.h
