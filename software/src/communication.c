/* tng-ao-4u-4i
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/tng/usb_stm32/usb.h"
#include "dac8760.h"

TNGHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_SET_VALUES: return set_values(message);
		case FID_GET_VALUES: return get_values(message, response);
		case FID_SET_VOLTAGES: return set_voltages(message);
		case FID_GET_VOLTAGES: return get_voltages(message, response);
		case FID_SET_CURRENTS: return set_currents(message);
		case FID_GET_CURRENTS: return get_currents(message, response);
		case FID_SET_SELECTED_VOLTAGE: return set_selected_voltage(message);
		case FID_GET_SELECTED_VOLTAGE: return get_selected_voltage(message, response);
		case FID_SET_SELECTED_CURRENT: return set_selected_current(message);
		case FID_GET_SELECTED_CURRENT: return get_selected_current(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


TNGHandleMessageResponse set_values(const SetValues *data) {
	for(uint8_t i = 0; i < DAC8760_VOLTAGE_NUM; i++) {
		dac8760.voltage[i] = data->voltages[i];
		dac8760.current[i] = data->currents[i];
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

TNGHandleMessageResponse get_values(const GetValues *data, GetValues_Response *response) {
	response->header.length = sizeof(GetValues_Response);
	response->timestamp     = system_timer_get_us();
	for(uint8_t i = 0; i < DAC8760_VOLTAGE_NUM; i++) {
		response->voltages[i] = dac8760.voltage[i];
		response->currents[i] = dac8760.current[i];
	}

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

TNGHandleMessageResponse set_voltages(const SetVoltages *data) {
	for(uint8_t i = 0; i < DAC8760_VOLTAGE_NUM; i++) {
		dac8760.voltage[i] = data->voltages[i];
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

TNGHandleMessageResponse get_voltages(const GetVoltages *data, GetVoltages_Response *response) {
	response->header.length = sizeof(GetVoltages_Response);
	response->timestamp     = system_timer_get_us();
	for(uint8_t i = 0; i < DAC8760_VOLTAGE_NUM; i++) {
		response->voltages[i] = dac8760.voltage[i];
	}

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

TNGHandleMessageResponse set_currents(const SetCurrents *data) {
	for(uint8_t i = 0; i < DAC8760_CURRENT_NUM; i++) {
		dac8760.current[i] = data->currents[i];
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

TNGHandleMessageResponse get_currents(const GetCurrents *data, GetCurrents_Response *response) {
	response->header.length = sizeof(GetCurrents_Response);
	response->timestamp     = system_timer_get_us();
	for(uint8_t i = 0; i < DAC8760_CURRENT_NUM; i++) {
		response->currents[i] = dac8760.current[i];
	}

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

TNGHandleMessageResponse set_selected_voltage(const SetSelectedVoltage *data) {
	if(data->channel >= DAC8760_VOLTAGE_NUM) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	dac8760.voltage[data->channel] = data->voltage;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

TNGHandleMessageResponse get_selected_voltage(const GetSelectedVoltage *data, GetSelectedVoltage_Response *response) {
	if(data->channel >= DAC8760_VOLTAGE_NUM) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	response->header.length = sizeof(GetSelectedVoltage_Response);
	response->timestamp     = system_timer_get_us();
	response->voltage       = dac8760.voltage[data->channel];

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

TNGHandleMessageResponse set_selected_current(const SetSelectedCurrent *data) {
	if(data->channel >= DAC8760_CURRENT_NUM) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	dac8760.current[data->channel] = data->current;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

TNGHandleMessageResponse get_selected_current(const GetSelectedCurrent *data, GetSelectedCurrent_Response *response) {
	if(data->channel >= DAC8760_CURRENT_NUM) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	response->header.length = sizeof(GetSelectedCurrent_Response);
	response->timestamp     = system_timer_get_us();
	response->current       = dac8760.current[data->channel];

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}


void communication_tick(void) {
//	communication_callback_tick();
}

void communication_init(void) {
//	communication_callback_init();
}
