#include "tests.h"

#include "codecEngineWrap/trikognitionCE.h"
#include "codecEngineWrap/denoiser.h"


void dspTest()
{
	TrikognitionCE ce();
	ce.setServerName("dsp_server.xe674");
	ce.setServerPath("/home/evgeniy/projects/trik/soundSensor/SoundSensor/dsp_server/trik/iaudenc1_denoise/dsp_server/bin/");
	ce.open();

	Denoiser denoiser(ce);

	denoiser.testProcess();
}
