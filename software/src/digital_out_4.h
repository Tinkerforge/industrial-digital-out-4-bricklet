/* industrial-digital-out-4-bricklet
 * Copyright (C) 2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * digital_out_4.h: Implementation of Industrial Digital Out 4 Bricklet messages
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef DIGITAL_OUT_4_H
#define DIGITAL_OUT_4_H

#include <stdint.h>

#include "bricklib/com/com_common.h"

#define FID_SET_VALUE 1
#define FID_GET_VALUE 2
#define FID_SET_MONOFLOP 3
#define FID_GET_MONOFLOP 4
#define FID_SET_GROUP 5
#define FID_GET_GROUP 6
#define FID_GET_AVAILABLE_FOR_GROUP 7
#define FID_MONOFLOP_DONE 8

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetValue;

typedef struct {
	MessageHeader header;
	uint16_t value_mask;
} __attribute__((__packed__)) GetValueReturn;

typedef struct {
	MessageHeader header;
	uint16_t value_mask;
} __attribute__((__packed__)) SetValue;

typedef struct {
	MessageHeader header;
	uint16_t pin_mask;
	uint16_t value_mask;
	uint32_t time;
} __attribute__((__packed__)) SetMonoflop;

typedef struct {
	MessageHeader header;
	uint8_t pin;
} __attribute__((__packed__)) GetMonoflop;

typedef struct {
	MessageHeader header;
	uint16_t value;
	uint32_t time;
	uint32_t time_remaining;
} __attribute__((__packed__)) GetMonoflopReturn;

typedef struct {
	MessageHeader header;
	char group[4];
} __attribute__((__packed__)) SetGroup;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetGroup;

typedef struct {
	MessageHeader header;
	char group[4];
} __attribute__((__packed__)) GetGroupReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetAvailableForGroup;

typedef struct {
	MessageHeader header;
	uint8_t available;
} __attribute__((__packed__)) GetAvailableForGroupReturn;

typedef struct {
	MessageHeader header;
	uint16_t pin_mask;
	uint16_t value_mask;
} __attribute__((__packed__)) MonoflopDone;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) StandardMessage;

void get_value(const ComType com, const GetValue *data);
void set_value(const ComType com, const SetValue *data);
void set_monoflop(const ComType com, const SetMonoflop *data);
void get_monoflop(const ComType com, const GetMonoflop *data);
void set_group(const ComType com, const SetGroup *data);
void get_group(const ComType com, const GetGroup *data);
void get_available_for_group(const ComType com, const GetAvailableForGroup *data);

uint16_t make_value(void);
void reconfigure_group(void);
void reconfigure_pins(void);
void invocation(const ComType com, const uint8_t *data);
void constructor(void);
void destructor(void);
void tick(const uint8_t tick_type);

#endif
