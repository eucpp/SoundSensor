#include "trikognitionCE.h"

TrikognitionCE::TrikognitionCE(QObject *parent) :
	CodecEngine(parent)
{
}

AUDENC1_Handle TrikognitionCE::createAUDENC1() const
{
	return AUDENC1_create(handle(), "TRIK_IAUDENC1_DENOISE", NULL);
}
