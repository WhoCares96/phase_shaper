/**
 * @file phase_shaper_meta.h
 * @author Arne Kuhle
 * @date 30 Sep 2021
 * @description here
 */


#ifndef ps_meta
#define ps_meta

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct phase_shaper_meta{
    int nFilters;
    float sampleRate;
    float f0;
    float Q;
    float mix;
    struct biquad_allpass *allpass_head;

} phase_shaper_meta;

phase_shaper_meta *phase_shaper_meta_new(float f0, float Q, float nFilters, float mix);

void phase_shaper_meta_free(phase_shaper_meta *x);

void phase_shaper_meta_setFrequency(phase_shaper_meta *x, float f0);

void phase_shaper_meta_setQ(phase_shaper_meta *x, float Q);

void phase_shaper_meta_setMix(phase_shaper_meta *x, float mix);

void phase_shaper_meta_setFilterCount(phase_shaper_meta *x, float nFilters);

void phase_shaper_meta_updateAllpassInstances(phase_shaper_meta *x);

void phase_shaper_meta_process(phase_shaper_meta *x, float *in, float *out, int vectorSize);

#ifdef __cplusplus
}
#endif

#endif
