#include "../include/internal/denoise.h"


void denoise(const float* signal_with_noise, const float* noise,
                 float* filter_impulse_response, float* signal,
                 int samplesNum, float error, const float adaptation_range)
{
    size_t size = 2 * samplesNum * sizeof(float) + sizeof(float);
    float* x = (float*) malloc(size);
    memset(x, 0, size);
    memcpy((++x) + samplesNum * sizeof(float), signal_with_noise, samplesNum * sizeof(float));

    float* y = (float*) malloc(samplesNum * sizeof(float));
    memset(y, 0, samplesNum * sizeof(float));

    float final_adapt_err = 0;
    #ifdef TEST
        final_adapt_err = DSPF_sp_lms_cn(++x, filter_impulse_response, noise, y,
                                        adaptation_range, error, samplesNum, samplesNum);
        DSPF_sp_w_vec_cn(y, signal_with_noise, -1, signal, samplesNum);
    #else
        final_adapt_err = DSPF_sp_lms(++x, filter_impulse_response, noise, y,
                                      adaptation_range, error, samplesNum, samplesNum);
        DSPF_sp_w_vec(y, signal_with_noise, -1, signal, samplesNum);
    #endif

    free(x);
    free(y);
}

#ifndef TEST

void test_fillOutBuff(XDM1_BufDesc* outBuff)
{
    outBuff->numBufs = 1;

    XDM_SETACCESSMODE_READ(outBuff->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBuff->descs[0].accessMask);

    outBuff->descs[0].bufSize = 10;
    for (int i = 0; i < outBuff->descs[0].bufSize; i++) {
        outBuff->descs[0].buf[i] = 0;
    }

    return;
}

#endif



