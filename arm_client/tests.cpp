#include <QDebug>

#include "tests.h"

#include "codecEngineWrap/codecEngine.h"
#include "codecEngineWrap/denoiser.h"


void dspTest()
{
	qDebug() << "create ce";
	trik::CodecEngine ce;
	ce.setServerName("dsp_server");
	ce.setServerPath("dsp_server.xe674");

	qDebug() << "open engine";
	ce.open();

	Denoiser denoiser(ce);

	denoiser.testProcess();
}
