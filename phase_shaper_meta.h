/**
 * @file phase_shaper_meta.h
 * @author Arne Kuhle <br>
 * @date 30 Sep 2021
 * @brief Wrapper for hosting allpass filters.<br>
 *
 * phase_shaper_meta wraps around the biquad_allpass class.<br>
 * It contains a variable amount of allpass instances and propagates parameter changes to each instances. <br>
 * It also performs the audio processing for each filter instance in a series.<br>
 * The filter instances are being stored in a linked list.<br>
 */

#ifndef ps_meta
#define ps_meta

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct phase_shaper_meta
 * @brief The wrapper struct for the audio processing job <br>
 */
typedef struct phase_shaper_meta{
    int nFilters; /**< The amount of serial processing filters */
    float sampleRate; /**< The sample rate of the incoming audio stream */
    float f0; /**< The center frequency of the filters */
    float Q; /**< The q factor of the filters */
    float mix; /**< the dry wet mix of the phase shaper */
    struct biquad_allpass *allpass_head; /**< Pointer to the first allpass filter instance */
} phase_shaper_meta;

/**
 * @related phase_shaper_meta
 * @brief Creates a new phase_shaper_meta object <br>
 * @returns an instance of the phase_shaper_meta object <br>
 * @param f0 The filters center frequency parameter <br>
 * @param Q The filters q factor parameter <br>
 * @param nFilters the amount of allpass filters <br>
 * @param mix The filters dry-wet mix parameter <br>
 */
phase_shaper_meta *phase_shaper_meta_new(float f0, float Q, float nFilters, float mix);

/**
 * @related phase_shaper_meta
 * @brief Frees the phase_shaper_meta object. <br>
 * @param x A pointer the phase_shaper_meta object <br>
 */
void phase_shaper_meta_free(phase_shaper_meta *x);

/**
 * @related phase_shaper_meta
 * @brief Sets the frequency adjustment parameter. <br>
 * @param x A pointer to the phase_shaper_meta object <br>
 * @param f0 Sets the frequency parameter <br>
 */
void phase_shaper_meta_setFrequency(phase_shaper_meta *x, float f0);

/**
 * @related phase_shaper_meta
 * @brief Sets the Q factor adjustment parameter. <br>
 * @param x A pointer to the phase_shaper_meta object <br>
 * @param Q Sets the frequency parameter <br>
 */
void phase_shaper_meta_setQ(phase_shaper_meta *x, float Q);

/**
 * @related phase_shaper_meta
 * @brief Sets the Dry-Wet Mix adjustment parameter. <br>
 * @param x A pointer to the phase_shaper_meta object <br>
 * @param mix Sets the Dry-Wet Mix parameter <br>
 */
void phase_shaper_meta_setMix(phase_shaper_meta *x, float mix);

/**
 * @related phase_shaper_meta
 * @brief Sets the filter count parameter. <br>
 * @param x A pointer to the phase_shaper_meta object <br>
 * @param nFilters Sets amount of Filters <br>
 */
void phase_shaper_meta_setFilterCount(phase_shaper_meta *x, float nFilters);

/**
 * @related phase_shaper_meta
 * @brief Updates filter parameters for each filter instance <br>
 * @param x A pointer to the phase_shaper_meta object <br>
 *
 * Propagates filter parameters of the meta instance to each filter instance. <br>
 * This is done by traversing through a linked list of filter instances and using the biquad_allpass setter methods for each instance.
 */
void phase_shaper_meta_updateAllpassInstances(phase_shaper_meta *x);

/**
 * @related phase_shaper_meta
 * @brief Process the incoming audio <br>
 * @param x A pointer to the phase_shaper_meta object <br>
 * @param in A pointer to audio input vector <br>
 * @param out A pointer to audio output vector <br>
 * @param vectorSize Size of the audio buffer <br>
 *
 * for each filter the biquad_allpass filter method gets called. <br>
 * This is done in a serial manner, meaning the filtered output of the last filter is used as input for the next filter. <br>
 */
void phase_shaper_meta_process(phase_shaper_meta *x, float *in, float *out, int vectorSize);

#ifdef __cplusplus
}
#endif

#endif
