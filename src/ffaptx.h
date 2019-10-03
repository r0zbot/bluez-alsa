//
// Created by t123yh on 2019/9/29.
//

#ifndef __FFAPTX_H_
#define __FFAPTX_H_
#include <stdint.h>
#include <stdbool.h>

enum aptx_channels
{
    LEFT,
    RIGHT,
    NB_CHANNELS
};

enum subbands
{
    LF,  // Low Frequency (0-5.5 kHz)
    MLF, // Medium-Low Frequency (5.5-11kHz)
    MHF, // Medium-High Frequency (11-16.5kHz)
    HF,  // High Frequency (16.5-22kHz)
    NB_SUBBANDS
};

#define NB_FILTERS 2
#define FILTER_TAPS 16

typedef struct
{
    int pos;
    int32_t buffer[2 * FILTER_TAPS];
} FilterSignal;

typedef struct
{
    FilterSignal outer_filter_signal[NB_FILTERS];
    FilterSignal inner_filter_signal[NB_FILTERS][NB_FILTERS];
} QMFAnalysis;

typedef struct
{
    int32_t quantized_sample;
    int32_t quantized_sample_parity_change;
    int32_t error;
} Quantize;

typedef struct
{
    int32_t quantization_factor;
    int32_t factor_select;
    int32_t reconstructed_difference;
} InvertQuantize;

typedef struct
{
    int32_t prev_sign[2];
    int32_t s_weight[2];
    int32_t d_weight[24];
    int32_t pos;
    int32_t reconstructed_differences[48];
    int32_t previous_reconstructed_sample;
    int32_t predicted_difference;
    int32_t predicted_sample;
} Prediction;

typedef struct
{
    int32_t codeword_history;
    int32_t dither_parity;
    int32_t dither[NB_SUBBANDS];
    
    QMFAnalysis qmf;
    Quantize quantize[NB_SUBBANDS];
    InvertQuantize invert_quantize[NB_SUBBANDS];
    Prediction prediction[NB_SUBBANDS];
} Channel;

typedef struct
{
    int hd;
    int block_size;
    int32_t sync_idx;
    Channel channels[NB_CHANNELS];
} AptXContext;

int ff_aptx_init(AptXContext* aptx, bool hd);
int ff_aptx_decode_samples(AptXContext *ctx,
                        const uint8_t *input,
                        int32_t samples[NB_CHANNELS][4]);
void ff_aptx_encode_samples(AptXContext *ctx,
                         int32_t samples[NB_CHANNELS][4],
                         uint8_t *output);
#endif //__FFAPTX_H_
