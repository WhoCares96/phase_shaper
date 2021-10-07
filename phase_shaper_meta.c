/*
 * TODO: Credits, Dokumentation, semikolon, formatierung, error fangen (z.b. nFilters muss >=1)
 */

#include "phase_shaper_meta.h"
#include "biquad_allpass.h"
#include "vas_mem.h"


phase_shaper_meta *phase_shaper_meta_new(float f0, float Q, float nFilters, float mix){

    phase_shaper_meta *x = (phase_shaper_meta *) vas_mem_alloc(sizeof(phase_shaper_meta));

    x->sampleRate = 44100;


    x->f0 = f0;
    x->Q = Q;
    x->mix = mix;
    x->nFilters = nFilters;

    x->allpass_head = biquad_allpass_new(x->f0, x->Q, x->mix);

    phase_shaper_meta_setFilterCount(x, x->nFilters);
    phase_shaper_meta_updateAllpassInstances(x);

    return x;
}


void phase_shaper_meta_free(phase_shaper_meta *x){

    // free allpasses
    phase_shaper_meta_setFilterCount(x, 1);
    biquad_allpass_free(x->allpass_head);

    // free phase_shaper_meta
    vas_mem_free(x);
}


void phase_shaper_meta_setFilterCount(phase_shaper_meta *x, float nFilters){

    // cast filter count to int
    nFilters = (int) nFilters;

    while (x->nFilters < nFilters) {

        biquad_allpass *current_allpass = x->allpass_head;

        // move to last element
        while (current_allpass->next != NULL) {
          current_allpass = current_allpass->next;
        }

        // push new allpass
        current_allpass->next = biquad_allpass_new(x->f0, x->Q, x->mix);

        x->nFilters = x->nFilters + 1;
    }


    while (x->nFilters > nFilters) {

        biquad_allpass *current_allpass = x->allpass_head;

        // move to second last element
        while (current_allpass->next->next != NULL) {
            current_allpass = current_allpass->next;
        }

        // pop last allpass
        biquad_allpass_free(current_allpass->next);
        current_allpass->next = NULL;

        x->nFilters = x->nFilters - 1;
    }

}


void phase_shaper_meta_updateAllpassInstances(phase_shaper_meta *x){

    biquad_allpass * current_allpass = x->allpass_head;

    while (current_allpass != NULL) {

        biquad_allpass_setFrequency(current_allpass, x->f0);
        biquad_allpass_setQ(current_allpass, x->Q);
        biquad_allpass_setMix(current_allpass, x->mix);

        biquad_allpass_updateParameters(current_allpass);

        current_allpass = current_allpass->next;
  }
}


void phase_shaper_meta_setQ(phase_shaper_meta *x, float Q){
    x->Q = Q;
    phase_shaper_meta_updateAllpassInstances(x);
}


void phase_shaper_meta_setFrequency(phase_shaper_meta *x, float f0){
    x->f0 = f0;
    phase_shaper_meta_updateAllpassInstances(x);
}


void phase_shaper_meta_setMix(phase_shaper_meta *x, float mix){
    x->mix = mix;
    phase_shaper_meta_updateAllpassInstances(x);
}


void phase_shaper_meta_process(phase_shaper_meta *x, float *in, float *out, int vectorSize){

    biquad_allpass *current_allpass = x->allpass_head;

    while (current_allpass != NULL) {

        biquad_allpass_filter_audio(current_allpass, in, out, vectorSize);

        in = out;

        current_allpass = current_allpass->next;
    }
}
