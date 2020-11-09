/*
 * BlueALSA - sbc.h
 * Copyright (c) 2016-2020 Arkadiusz Bokowy
 *
 * This file is a part of bluez-alsa.
 *
 * This project is licensed under the terms of the MIT license.
 *
 */

#ifndef BLUEALSA_SBC_H_
#define BLUEALSA_SBC_H_

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdint.h>
#include <sbc/sbc.h>
#include "a2dp-codecs.h"

#define SBC_QUALITY_LOW    0
#define SBC_QUALITY_MEDIUM 1
#define SBC_QUALITY_HIGH   2
#define SBC_QUALITY_XQ     3

uint8_t sbc_a2dp_get_bitpool(const a2dp_sbc_t *conf, unsigned int quality);

#if DEBUG
void sbc_print_internals(const sbc_t *sbc);
#endif

#endif
