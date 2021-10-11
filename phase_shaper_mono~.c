/**
 * @file "phase_shaper_mono~.c"
 * @author Arne Kuhle <br>
 * @brief A Pure Data object for filtering an incoming signal with a series of allpass filters.<br>
 *
 * phase_shaper~ is a sound design tool. Mono Version (1 Channel).<br>
 * The incoming audio signal is transformed by a variable length series of allpass filters.<br>
 * The induced phase shift creates an audible delay at the filters center frequency.<br>
 * This can be used to transform audio material in various ways e.g. enhancing a kickdrum's fundamental frequency.<br>
 * The dry-wet mix parameter can additionally be used to create phase cancellations which can drastically filter incoming audio.<br>
 */

#include "m_pd.h"
#include "biquad_allpass.h"
#include "phase_shaper_meta.h"
#include "vas_mem.h"

static t_class *phase_shaper_mono_tilde_class;

/**
 * @struct phase_shaper_mono_tilde
 * @brief The Pure Data struct of the phase_shaper~ object. <br>
 */
typedef struct phase_shaper_mono_tilde{
    t_object  x_obj; /**< Necessary for every signal object in Pure Data */
    t_sample f; /**< Necessary for signal objects, float dummy dataspace for converting a float to signal if no signal is connected (CLASS_MAINSIGNALIN) */
    phase_shaper_meta *p_meta; /**< The the phase shaper meta object for actual signal processing */
    t_outlet *x_out; /**< A signal outlet for the filtered signal */
} phase_shaper_mono_tilde;

/**
 * @related phase_shaper_mono_tilde
 * @brief Calculates ta allpass filtered output vector<br>
 * @param w A pointer to the object, input and output vectors. <br>
 * The function calls the phase_shaper_meta_process method. <br>
 * @return A pointer to the signal chain right behind the phase_shaper_mono_tilde_perform object. <br>
 */
t_int *phase_shaper_mono_tilde_perform(t_int *w)
{
    phase_shaper_mono_tilde *x = (phase_shaper_mono_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    phase_shaper_meta_process(x->p_meta, in, out, n);

    return (w+5);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Adds phase_shaper_mono_tilde_perform to the signal chain. <br>
 * @param x A pointer to the rtap_biquad_tilde object <br>
 * @param sp A pointer to the input and output vectors <br>
 */
void phase_shaper_mono_tilde_dsp(phase_shaper_mono_tilde *x, t_signal **sp)
{
    dsp_add(phase_shaper_mono_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Frees the phase_shaper_meta object. <br>
 * @param x A pointer the phase_shaper_mono_tilde object <br>
 */
void phase_shaper_mono_tilde_free(phase_shaper_mono_tilde *x){
    outlet_free(x->x_out);
    phase_shaper_meta_free(x->p_meta);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Creates a new phase_shaper_mono_tilde object <br>
 * @returns an instance of the phase_shaper_mono_tilde object <br>
 */
void *phase_shaper_mono_tilde_new(){
    phase_shaper_mono_tilde *x = (phase_shaper_mono_tilde *)pd_new(phase_shaper_mono_tilde_class);

    x->x_out = outlet_new(&x->x_obj, &s_signal);
    x->p_meta = phase_shaper_meta_new(1000, 10, 1, 1);

    return (void *)x;
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Sets the frequency adjustment parameter. <br>
 * @param x A pointer to the phase_shaper_mono_tilde object <br>
 * @param freq Sets the frequency parameter <br>
 */
void phase_shaper_mono_tilde_setFrequency(phase_shaper_mono_tilde *x, float freq){
    phase_shaper_meta_setFrequency(x->p_meta, freq);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Sets the Q factor adjustment parameter. <br>
 * @param x A pointer to the phase_shaper_mono_tilde object <br>
 * @param Q Sets the q factor parameter <br>
 */
void phase_shaper_mono_tilde_setQ(phase_shaper_mono_tilde *x, float Q){
    phase_shaper_meta_setQ(x->p_meta, Q);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Sets the filter count parameter. <br>
 * @param x A pointer to the phase_shaper_mono_tilde object <br>
 * @param nFilters Sets amount of Filters <br>
 */
void phase_shaper_mono_tilde_setFilterCount(phase_shaper_mono_tilde *x, float nFilters){
    phase_shaper_meta_setFilterCount(x->p_meta, nFilters);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Sets the Dry-Wet Mix adjustment parameter. <br>
 * @param x A pointer to the phase_shaper_mono_tilde object <br>
 * @param mix Sets the Dry-Wet Mix parameter <br>
 */
void phase_shaper_mono_tilde_setMix(phase_shaper_mono_tilde *x, float mix){
    phase_shaper_meta_setMix(x->p_meta, mix);
}

/**
 * @related phase_shaper_mono_tilde
 * @brief Setup for the phase_shaper_mono_tilde class <br>
 */
void phase_shaper_mono_tilde_setup(void){
      phase_shaper_mono_tilde_class = class_new(gensym("phase_shaper_mono~"),
            (t_newmethod)phase_shaper_mono_tilde_new,
            (t_method)phase_shaper_mono_tilde_free,
            sizeof(phase_shaper_mono_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(phase_shaper_mono_tilde_class, (t_method)phase_shaper_mono_tilde_dsp, gensym("dsp"), 0);

      class_addmethod(phase_shaper_mono_tilde_class, (t_method)phase_shaper_mono_tilde_setFrequency, gensym("freq"), A_DEFFLOAT, 0);

      class_addmethod(phase_shaper_mono_tilde_class, (t_method)phase_shaper_mono_tilde_setQ, gensym("q"), A_DEFFLOAT, 0);

      class_addmethod(phase_shaper_mono_tilde_class, (t_method)phase_shaper_mono_tilde_setFilterCount, gensym("filtercount"), A_DEFFLOAT, 0);

      class_addmethod(phase_shaper_mono_tilde_class, (t_method)phase_shaper_mono_tilde_setMix, gensym("mix"), A_DEFFLOAT, 0);

      CLASS_MAINSIGNALIN(phase_shaper_mono_tilde_class, phase_shaper_mono_tilde, f);
}
