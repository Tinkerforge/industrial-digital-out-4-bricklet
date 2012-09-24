/* industrial-digital-out-4-bricklet
 * Copyright (C) 2012 Olaf Lüke <olaf@tinkerforge.com>
 *
 * digital_out_4.c: Implementation of Industrial Digital Out 4 Bricklet messages
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

#include "digital_out_4.h"

#include "brickletlib/bricklet_entry.h"
#include "bricklib/utility/mutex.h"
#include "bricklib/utility/init.h"
#include "bricklib/bricklet/bricklet_communication.h"
#include "config.h"
#include <pio/pio_it.h>
#include <pio/pio.h>

const ComMessage com_messages[] = {
	{TYPE_SET_VALUE, (message_handler_func_t)set_value},
	{TYPE_GET_VALUE, (message_handler_func_t)get_value},
	{TYPE_SET_MONOFLOP, (message_handler_func_t)set_monoflop},
	{TYPE_GET_MONOFLOP, (message_handler_func_t)get_monoflop},
	{TYPE_SET_GROUP, (message_handler_func_t)set_group},
	{TYPE_GET_GROUP, (message_handler_func_t)get_group},
	{TYPE_GET_AVAILABLE_FOR_GROUP, (message_handler_func_t)get_available_for_group},
};

void invocation(uint8_t com, uint8_t *data) {
	uint8_t id = ((StandardMessage*)data)->type - 1;
	if(id < NUM_MESSAGES) {
		BRICKLET_OFFSET(com_messages[id].reply_func)(com, data);
	}
}

void constructor(void) {
	_Static_assert(sizeof(BrickContext) <= BRICKLET_CONTEXT_MAX_SIZE, "BrickContext too big");

	BC->magic_number1 = MAGIC_NUMBER_INDUSTRIAL_DIGITAL_OUT_4_1;
	BC->magic_number2 = MAGIC_NUMBER_INDUSTRIAL_DIGITAL_OUT_4_2;

	BC->group[0] = 'n';
	BC->group[1] = 'n';
	BC->group[2] = 'n';
	BC->group[3] = 'n';

	reconfigure_group();

	reconfigure_pins();
	BC->monoflop_callback_mask = 0;
	BC->counter = 0;
}

void destructor(void) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i] != NULL) {
			BC->pins[i]->type = PIO_INPUT;
			BC->pins[i]->attribute = PIO_PULLUP;
			BA->PIO_Configure(BC->pins[i], NUM_PINS);
		}
	}
}

void reconfigure_pins(void) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i] != NULL) {
			BC->pins[i]->type = PIO_OUTPUT_1;
			BC->pins[i]->attribute = PIO_DEFAULT;
			BC->time[i] = 0;
			BC->time_remaining[i] = 0;
			BA->PIO_Configure(BC->pins[i], 1);
		}
	}
}

uint16_t make_value(void) {
	uint16_t value = 0;
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i] != NULL) {
			if(!(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask)) {
				value |= (1 << i);
			}
		}
	}

	return value;
}

bool is_group_available(char group) {
	const int8_t diff = BS->port - group;
	return (BCO(diff)->magic_number1 == MAGIC_NUMBER_INDUSTRIAL_DIGITAL_OUT_4_1) &&
	       (BCO(diff)->magic_number2 == MAGIC_NUMBER_INDUSTRIAL_DIGITAL_OUT_4_2);
}

void reconfigure_group(void) {
	if(BC->group[0] == 'n' && BC->group[1] == 'n' && BC->group[2] == 'n' && BC->group[3] == 'n') {
		BC->pins[0] = &PIN0;
		BC->pins[1] = &PIN1;
		BC->pins[2] = &PIN2;
		BC->pins[3] = &PIN3;
		BC->pins[4] = NULL;
		BC->pins[5] = NULL;
		BC->pins[6] = NULL;
		BC->pins[7] = NULL;
		BC->pins[8] = NULL;
		BC->pins[9] = NULL;
		BC->pins[10] = NULL;
		BC->pins[11] = NULL;
		BC->pins[12] = NULL;
		BC->pins[13] = NULL;
		BC->pins[14] = NULL;
		BC->pins[15] = NULL;
	} else {
		for(uint8_t i = 0; i < 4; i++) {
			const uint8_t start = i*4;
			const int8_t diff = BS->port - BC->group[i];
			if(diff > -4 && diff < 4) {
				BC->pins[start] = &BSO(diff)->pin1_ad;
				BC->pins[start+1] = &BSO(diff)->pin2_da;
				BC->pins[start+2] = &BSO(diff)->pin3_pwm;
				BC->pins[start+3] = &BSO(diff)->pin4_io;
			} else {
				BC->pins[start] = NULL;
				BC->pins[start+1] = NULL;
				BC->pins[start+2] = NULL;
				BC->pins[start+3] = NULL;
			}
		}
	}
}

void tick(uint8_t tick_type) {
	if(tick_type & TICK_TASK_TYPE_CALCULATION) {
		if(BC->counter != 0) {
			BC->counter--;
		}

		for(uint8_t i = 0; i < NUM_PINS; i++) {
			if(BC->time_remaining[i] != 0) {
				BC->time_remaining[i]--;
				if(BC->time_remaining[i] == 0) {
					if(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask) {
						BC->pins[i]->pio->PIO_CODR = BC->pins[i]->mask;
					} else {
						BC->pins[i]->pio->PIO_SODR = BC->pins[i]->mask;
					}
					BC->monoflop_callback_mask |= (1 << i);
				}
			}
		}
	}

	if(tick_type & TICK_TASK_TYPE_MESSAGE) {
		if(BC->monoflop_callback_mask) {
			MonoflopDone md = {
				BS->stack_id,
				TYPE_MONOFLOP_DONE,
				sizeof(MonoflopDone),
				0,
				0
			};

			for(uint8_t i = 0; i < NUM_PINS; i++) {
				if (BC->monoflop_callback_mask & (1 << i)) {
					md.pin_mask |= (1 << i);

					if(BC->pins[i]->pio->PIO_PDSR & BC->pins[i]->mask) {
						md.value_mask |= (1 << i);
					}
				}
			}

			BA->send_blocking_with_timeout(&md,
			                               sizeof(MonoflopDone),
			                               *BA->com_current);

			BC->monoflop_callback_mask = 0;
		}
	}
}

void get_value(uint8_t com, const GetValue *data) {
	GetValueReturn gvr;

	gvr.stack_id      = data->stack_id;
	gvr.type          = data->type;
	gvr.length        = sizeof(GetValueReturn);
	gvr.value_mask    = make_value();

	BA->send_blocking_with_timeout(&gvr, sizeof(GetValueReturn), com);
}

void set_value(uint8_t com, const SetValue *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if(BC->pins[i] != NULL) {
			if(data->value_mask & (1 << i)) {
				BC->pins[i]->pio->PIO_CODR = BC->pins[i]->mask;
			} else {
				BC->pins[i]->pio->PIO_SODR = BC->pins[i]->mask;
			}
		}
		BC->time_remaining[i] = 0;
	}
}

void set_monoflop(uint8_t com, SetMonoflop *data) {
	for(uint8_t i = 0; i < NUM_PINS; i++) {
		if((data->pin_mask & (1 << i))) {
			if(data->value_mask & (1 << i)) {
				BC->pins[i]->pio->PIO_CODR = BC->pins[i]->mask;
			} else {
				BC->pins[i]->pio->PIO_SODR = BC->pins[i]->mask;
			}

			BC->time[i] = data->time;
			BC->time_remaining[i] = data->time;
		}
	}
}

void get_monoflop(uint8_t com, GetMonoflop *data) {
	if(data->pin >= NUM_PINS) {
		// TODO: Error?
		return;
	}

	GetMonoflopReturn gmr;

	gmr.stack_id       = data->stack_id;
	gmr.type           = data->type;
	gmr.length         = sizeof(GetMonoflopReturn);
	gmr.value          = (BC->pins[data->pin]->pio->PIO_PDSR & BC->pins[data->pin]->mask) ? 1 : 0;
	gmr.time           = BC->time[data->pin];
	gmr.time_remaining = BC->time_remaining[data->pin];

	BA->send_blocking_with_timeout(&gmr, sizeof(GetMonoflopReturn), com);
}

void set_group(uint8_t com, SetGroup *data) {
	for(uint8_t i = 0; i < 4; i++) {
		if(data->group[i] < 'a') {
			data->group[i] += 'a' - 'A';
		}
		if(data->group[i] >= 'a' &&
           data->group[i] <= 'd' &&
           is_group_available(data->group[i])) {
			BC->group[i] = data->group[i];
		} else {
			BC->group[i] = 'n';
		}
	}

	reconfigure_group();
}

void get_group(uint8_t com, GetGroup *data) {
	GetGroupReturn ggr;

	ggr.stack_id       = data->stack_id;
	ggr.type           = data->type;
	ggr.length         = sizeof(GetGroupReturn);
	ggr.group[0]       = BC->group[0];
	ggr.group[1]       = BC->group[1];
	ggr.group[2]       = BC->group[2];
	ggr.group[3]       = BC->group[3];

	BA->send_blocking_with_timeout(&ggr, sizeof(GetGroupReturn), com);
}

void get_available_for_group(uint8_t com, GetAvailableForGroup *data) {
	GetAvailableForGroupReturn gafgr;

	gafgr.stack_id       = data->stack_id;
	gafgr.type           = data->type;
	gafgr.length         = sizeof(GetAvailableForGroupReturn);
	gafgr.available      = 0;

	for(uint8_t i = 0; i < 4; i++) {
		if(is_group_available((char)(i+'a'))) {
			gafgr.available |= (1 << i);
		}
	}

	BA->send_blocking_with_timeout(&gafgr, sizeof(GetAvailableForGroupReturn), com);
}
