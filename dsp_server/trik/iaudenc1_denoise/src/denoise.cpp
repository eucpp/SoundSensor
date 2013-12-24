#include "../include/internal/denoise.h"

//#ifdef __cplusplus
//extern "C" {
//#endif // __cplusplus

float denoise(const float* signal_with_noise, const float* noise,
                 float* filter_impulse_response, float* signal,
                 int samplesNum, float error, const float adaptation_range)
{
	const size_t filter_size = 20;
	size_t size = (samplesNum + filter_size + 1) * sizeof(float);
    float* x = (float*) malloc(size);
    memset(x, 0, size);
	memcpy(x + 1 + filter_size, signal_with_noise, samplesNum * sizeof(float));

    float* y = (float*) malloc(samplesNum * sizeof(float));
    memset(y, 0, samplesNum * sizeof(float));

    float final_adapt_err = 0;
    #ifdef TEST
        final_adapt_err = DSPF_sp_lms_cn(x + 1, filter_impulse_response, noise, y,
										adaptation_range, error, filter_size, samplesNum);
//        DSPF_sp_w_vec_cn(y, signal_with_noise, -1, signal, samplesNum);
		memcpy(signal, y, samplesNum * sizeof(float));
    #else
        final_adapt_err = DSPF_sp_lms(x + 1, filter_impulse_response, noise, y,
                                      adaptation_range, error, samplesNum, samplesNum);
        DSPF_sp_w_vec(y, signal_with_noise, -1, signal, samplesNum);
    #endif

    free(x);
    free(y);


    return final_adapt_err;
}

#ifndef TEST

void test_fillOutBuff(XDM1_BufDesc* outBuff)
{

    XDM_SETACCESSMODE_READ(outBuff->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBuff->descs[0].accessMask);

//	outBuff->numBufs = 1;

    outBuff->descs[0].bufSize = 10;
    for (int i = 0; i < outBuff->descs[0].bufSize; i++) {
		outBuff->descs[0].buf[i] = (XDAS_Int8)i;
    }

    return;
}

#endif

//#ifdef __cplusplus
//} // extern "C"
//#endif // __cplusplus

