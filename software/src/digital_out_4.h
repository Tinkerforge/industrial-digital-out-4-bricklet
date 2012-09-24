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

#define TYPE_SET_VALUE 1
#define TYPE_GET_VALUE 2
#define TYPE_SET_MONOFLOP 3
#define TYPE_GET_MONOFLOP 4
#define TYPE_SET_GROUP 5
#define TYPE_GET_GROUP 6
#define TYPE_GET_AVAILABLE_FOR_GROUP 7
#define TYPE_MONOFLOP_DONE 8

#define NUM_MESSAGES 8

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetValue;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t value_mask;
} __attribute__((__packed__)) GetValueReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t value_mask;
} __attribute__((__packed__)) SetValue;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t pin_mask;
	uint16_t value_mask;
	uint32_t time;
} __attribute__((__packed__)) SetMonoflop;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t pin;
} __attribute__((__packed__)) GetMonoflop;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t value;
	uint32_t time;
	uint32_t time_remaining;
} __attribute__((__packed__)) GetMonoflopReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	char group[4];
} __attribute__((__packed__)) SetGroup;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetGroup;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	char group[4];
} __attribute__((__packed__)) GetGroupReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetAvailableForGroup;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t available;
} __attribute__((__packed__)) GetAvailableForGroupReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t pin_mask;
	uint16_t value_mask;
} __attribute__((__packed__)) MonoflopDone;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) StandardMessage;

void get_value(uint8_t com, const GetValue *data);
void set_value(uint8_t com, const SetValue *data);
void set_monoflop(uint8_t com, SetMonoflop *data);
void get_monoflop(uint8_t com, GetMonoflop *data);
void set_group(uint8_t com, SetGroup *data);
void get_group(uint8_t com, GetGroup *data);
void get_available_for_group(uint8_t com, GetAvailableForGroup *data);

void reconfigure_group(void);
void reconfigure_pins(void);
void invocation(uint8_t com, uint8_t *data);
void constructor(void);
void destructor(void);
void tick(uint8_t tick_type);

#endif
