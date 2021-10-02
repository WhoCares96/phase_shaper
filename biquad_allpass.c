/*
 * TODO: Credits, Dokumentation
 */

#include "biquad_allpass.h"
#include "vas_mem.h"

biquad_allpass *biquad_allpass_new(float f0, float Q){

    biquad_allpass *x = (biquad_allpass *) vas_mem_alloc(sizeof(biquad_allpass));

    x->sampleRate = 44100;
    x->lastOut = 0;
    x->lastLastOut = 0;
    x->lastIn = 0;
    x->lastLastIn = 0;

    x->f0 = f0;
    x->Q = Q;
    x->gain = 1;

    x->next = NULL;

    biquad_allpass_updateParameters(x);
    return x;
}


void biquad_allpass_free(biquad_allpass *x){
    vas_mem_free(x);
}

void biquad_allpass_setQ(biquad_allpass *x, float Q){
    x->Q = Q;
    biquad_allpass_updateParameters(x);
}

void biquad_allpass_setFrequency(biquad_allpass *x, float f0){
    x->f0 = f0;
    biquad_allpass_updateParameters(x);
}

void biquad_allpass_updateParameters(biquad_allpass *x){
    x->A = sqrtf(powf(x->gain/20, 10));
    x->w0 = 2*M_PI*x->f0/x->sampleRate;
    x->cosW0 = cosf(x->w0);
    x->sinW0 = sinf(x->w0);
    x->alpha = x->sinW0/2*x->Q;

    // allpass coefficients
    x->a0 = 1 + x->alpha;
    x->a1 = -2 * x->cosW0;
    x->a2 = 1 - x->alpha;
    x->b0 = 1 - x->alpha;
    x->b1 = -2 * x->cosW0;
    x->b2 = 1 + x->alpha;

    x->b0_over_a0 = x->b0/x->a0;
    x->a1_over_a0 = x->a1/x->a0;
    x->a2_over_a0 = x->a2/x->a0;
    x->b1_over_a0 = x->b1/x->a0;
    x->b2_over_a0 = x->b2/x->a0;
}


void biquad_allpass_filter_audio(biquad_allpass *x, float *in, float *out, int vectorSize){
    float lastOut;
    float lastLastOut;
    float lastIn;
    float lastLastIn;

    float currentIn;
    float currentOut;

    lastOut = x->lastOut;
    lastLastOut = x->lastLastOut;
    lastIn = x->lastIn;
    lastLastIn = x->lastLastIn;

    for(int n=0; n<vectorSize; n++){
      currentIn = *(in+n);

      currentOut =    x->b0_over_a0 * currentIn
                    + x->b1_over_a0 * lastIn
                    + x->b2_over_a0 * lastLastIn
                    - x->a1_over_a0 * lastOut
                    - x->a2_over_a0 * lastLastOut;

      *(out+n) = currentOut;

      lastLastOut = lastOut;
      lastOut = currentOut;
      lastLastIn = lastIn;
      lastIn = currentIn;
    }

    x->lastLastIn = lastLastIn;
    x->lastIn = lastIn;
    x->lastLastOut = lastLastOut;
    x->lastOut = lastOut;
}
