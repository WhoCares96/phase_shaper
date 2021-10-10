/**
 * @file biquad_allpass.h
 * @author Arne Kuhle
 * @date 28 Jun 2021
 * @brief A simple biquad allpass filter
 */

#ifndef bq_allpass
#define bq_allpass

#include "math.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct biquad_allpass
 * @brief A struct for a biquad allpass filter <br>
 *
 * The biquad_allpass struct contains all variables needed for a single biquad allpass filter.
 * See: https://en.wikipedia.org/wiki/Digital_biquad_filter <br>
 */
typedef struct biquad_allpass{
    float sampleRate; /**< The sample rate of the incoming audio stream */
    float f0; /**< The center frequency of the filter */
    float lastOut; /**< The last processed audio sample */
    float lastLastOut; /**< The second last processed audio sample */
    float lastIn; /**< The last unprocessed audio sample */
    float lastLastIn; /**< The second last unprocessed audio sample */
    float Q; /**< The q factor of the filter */
    float w0; /**< The filters omega value */
    float cosW0; /**< The filters cos(omega) value */
    float sinW0; /**< The filters sin(omega) value */
    float alpha; /**< The filters alpha value */
    float mix; /**< The dry wet mix of the phase shaper */
    float a0; /**< Filter coefficient */
    float a1; /**< Filter coefficient */
    float a2; /**< Filter coefficient */
    float b0; /**< Filter coefficient */
    float b1; /**< Filter coefficient */
    float b2; /**< Filter coefficient */
    float b0_over_a0; /**< Pre-calculated fraction */
    float b1_over_a0; /**< Pre-calculated fraction */
    float b2_over_a0; /**< Pre-calculated fraction */
    float a1_over_a0; /**< Pre-calculated fraction */
    float a2_over_a0; /**< Pre-calculated fraction */
    struct biquad_allpass *next; /**< Pointer to the next allpass filter instance */
} biquad_allpass;

/**
 * @related biquad_allpass
 * @brief Creates a new biquad_allpass object <br>
 * @returns an instance of the biquad_allpass object <br>
 * @param f0 The filters center frequency parameter <br>
 * @param Q The filters q factor parameter <br>
 * @param mix The filters dry-wet mix parameter <br>
 * @param sampleRate The systems sample rate <br>
 */
biquad_allpass *biquad_allpass_new(float f0, float Q, float mix, float sampleRate);

/**
 * @related biquad_allpass
 * @brief Frees the biquad_allpass object. <br>
 * @param x A pointer the biquad_allpass object <br>
 */
void biquad_allpass_free(biquad_allpass *x);

/**
 * @related biquad_allpass
 * @brief Sets the frequency adjustment parameter. <br>
 * @param x A pointer to the biquad_allpass object <br>
 * @param f0 Sets the frequency parameter <br>
 */
void biquad_allpass_setFrequency(biquad_allpass *x, float f0);

/**
 * @related biquad_allpass
 * @brief Sets the Q factor adjustment parameter. <br>
 * @param x A pointer to the biquad_allpass object <br>
 * @param Q Sets the frequency parameter <br>
 */
void biquad_allpass_setQ(biquad_allpass *x, float Q);

/**
 * @related biquad_allpass
 * @brief Sets the Dry-Wet Mix adjustment parameter. <br>
 * @param x A pointer to the biquad_allpass object <br>
 * @param mix Sets the Dry-Wet Mix parameter <br>
 */
void biquad_allpass_setMix(biquad_allpass *x, float mix);

/**
 * @related biquad_allpass
 * @brief Calculates filter coefficients from set parameters <br>
 * @param x A pointer to the biquad_allpass object <br>
 */
void biquad_allpass_updateParameters(biquad_allpass *x);

/**
 * @related biquad_allpass
 * @brief Process the incoming audio <br>
 * @param x A pointer to the biquad_allpass object <br>
 * @param in A pointer to audio input buffer <br>
 * @param out A pointer to audio output buffer <br>
 * @param vectorSize Size of the audio buffer <br>
 *
 * Transforms the input samples given the biquad filter function and writes them to the output buffer. <br>
 * Updates the lastIn/lastOut parameters respectively. <br>
 */
void biquad_allpass_filter_audio(biquad_allpass *x, float *in, float *out, int vectorSize);

#ifdef __cplusplus
}
#endif

#endif
