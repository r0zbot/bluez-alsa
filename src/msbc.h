/*
 * BlueALSA - msbc.h
 * Copyright (c) 2016-2019 Arkadiusz Bokowy
 *
 * This file is a part of bluez-alsa.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#ifndef BLUEALSA_MSBC_H_
#define BLUEALSA_MSBC_H_

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <sbc/sbc.h>

#include "shared/ffb.h"

/* HFP uses SBC encoding with precisely defined parameters. Hence, the size
 * of the input (number of PCM samples) and output is known up front. */
#define MSBC_CODESIZE    240
#define MSBC_CODESAMPLES (MSBC_CODESIZE / sizeof(int16_t))
#define MSBC_FRAMELEN    57

#define ESCO_H2_SYNCWORD 0x801
#define ESCO_H2_GET_SYNCWORD(h2) ((h2) & 0xFFF)
#define ESCO_H2_GET_SN0(h2)      (((h2) >> 12) & 0x3)
#define ESCO_H2_GET_SN1(h2)      (((h2) >> 14) & 0x3)
/* Pack two repetition code protected 2-bit sequence numbers (both bits
 * duplicated) into the 16-bit eSCO H2 header. Note, that after packing,
 * the H2 header value has to be converted to little-endian. */
#define ESCO_H2_PACK(sn0, sn1) (ESCO_H2_SYNCWORD | (sn0) << 12 | (sn1) << 14)

typedef uint16_t esco_h2_header_t;
typedef struct esco_msbc_frame {
	esco_h2_header_t header;
	uint8_t payload[MSBC_FRAMELEN];
	uint8_t padding;
} __attribute__ ((packed)) esco_msbc_frame_t;

struct esco_msbc {

	/* decoder */
	sbc_t dec_sbc;
	/* encoder */
	sbc_t enc_sbc;

	/* buffer for incoming eSCO frames */
	ffb_t dec_data;
	/* buffer for outgoing PCM samples */
	ffb_t dec_pcm;

	/* buffer for incoming PCM samples */
	ffb_t enc_pcm;
	/* buffer for outgoing eSCO frames */
	ffb_t enc_data;

	uint8_t dec_seq_initialized : 1;
	uint8_t dec_seq_number : 2;
	uint8_t enc_seq_number : 2;
	size_t enc_frames;

	/* Determine whether structure has been initialized. This field is
	 * used for reinitialization - it makes msbc_init() idempotent. */
	bool initialized;

};

int msbc_init(struct esco_msbc *msbc);
void msbc_finish(struct esco_msbc *msbc);

int msbc_decode(struct esco_msbc *msbc);
int msbc_encode(struct esco_msbc *msbc);

#endif
