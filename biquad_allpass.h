/**
 * @file biquad_allpass.h
 * @author Thomas Resch
 * @adapted by Arne Kuhle
 * @date 28 Jun 2021
 * @brief Biquad Filter
 */

// TODO unnätige variablen entfernen

#ifndef bq_allpass
#define bq_allpass

#include "math.h"
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct biquad_allpass{
    float sampleRate;
    float f0;
    float lastOut;
    float lastLastOut;
    float lastIn;
    float lastLastIn;
    float Q;
    float bandwidth;
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
    struct biquad_allpass *next;

} biquad_allpass;

biquad_allpass *biquad_allpass_new(float f0, float Q);

void biquad_allpass_free(biquad_allpass *x);

void biquad_allpass_setFrequency(biquad_allpass *x, float f0);

void biquad_allpass_setQ(biquad_allpass *x, float Q);

void biquad_allpass_updateParameters(biquad_allpass *x);

void biquad_allpass_filter_audio(biquad_allpass *x, float *in, float *out, int vectorSize);

#ifdef __cplusplus
}
#endif

#endif
