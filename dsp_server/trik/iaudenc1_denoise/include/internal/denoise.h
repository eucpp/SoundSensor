#ifndef DENOISE
#define DENOISE

//#define TEST

#ifdef TEST
    #include <ti/dsplib/src/DSPF_sp_lms/c674/DSPF_sp_lms_cn.h>
    #include <ti/dsplib/src/DSPF_sp_w_vec/c674/DSPF_sp_w_vec_cn.h>
#else
    #include <xdc/std.h>
    #include <ti/xdais/ialg.h>
    #include <ti/xdais/dm/iaudenc1.h>

    #include <ti/dsplib/src/DSPF_sp_lms/c674/DSPF_sp_lms.h>
    #include <ti/dsplib/src/DSPF_sp_w_vec/c674/DSPF_sp_w_vec.h>
#endif

#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/**
 * @brief denoise
 *
 * @param[in] signal_with_noise pointer to the array of signal samples.
 * @param[in] noise pointer to the array of noise samples.
 * @param[out] filter_impulse_response pointer to adapted filter.
 * @param[out] signal pointer to denoised signal.
 * @param[in] samplesNum num of samples of signal and noise (and filter_impulse_response also).
 * @param[in] error Initial adaptation error. Used to update the filter taps on the first iteration.
 * @param[in] adaptation_range Adaptation rate (or step size) for the LMS process.
 *                         This value controls how drastically the LMS filter coefficients change with each iteration,
 *                         and it is typically set to a small fractional value.
 *                         A high adaptation rate can destabilize the LMS algorithm.
 */
float denoise(const float* signal_with_noise, const float* noise,
             float* filter_impulse_response, float* signal,
             int samplesNum, float error, const float adaptation_range);


//#ifndef TEST

void test_fillOutBuff(XDM1_BufDesc* outBuff);

//#endif


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif
