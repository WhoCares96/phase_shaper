/**
 * @file vas_highpass.h
 * @author Thomas Resch
 * @date 4 Jan 2018
 * @brief Biquad Filter <br>
 * From Robert Bristow-Johnson's Webpage
 * http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
 *
 */


#ifndef biquad_h
#define biquad_h

#include "vas_mem.h"
#include "math.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vas_l{
    int nFilters;
    float sampleRate;
    float f0;
    float lastOut;
    float lastLastOut;
    float lastIn;
    float lastLastIn;
    float Q;
    float bandwidth;
    float shelfSlope;
    float A;
    float w0;
    float cosW0;
    float sinW0;
    float alpha;
    float gain;
    float a0, a1, a2, b0, b1, b2;
    float b0_over_a0;
    float b1_over_a0;
    float b2_over_a0;
    float a1_over_a0;
    float a2_over_a0;

} biquad_allpass;

biquad_allpass *biquad_allpass_new(float f0, float Q, float nFilters);

void biquad_allpass_free(biquad_allpass *x);

void biquad_allpass_setFrequency(biquad_allpass *x, float f0);

void biquad_allpass_setQ(biquad_allpass *x, float Q);

void biquad_allpass_setFilterCount(biquad_allpass *x, float nFilters);

void biquad_allpass_process(biquad_allpass *x, float *in, float *out, int vectorSize);

#ifdef __cplusplus
}
#endif

#endif
