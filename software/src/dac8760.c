/* tng-ao-4u-4i
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dac8760.c: Driver for DAC8760 DAC
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

#include "dac8760.h"

#include "configs/config_dac8760.h"
#include "bricklib2/logging/logging.h"
#include "bricklib2/utility/crc8.h"
#include "bricklib2/utility/util_definitions.h"
#include "bricklib2/tng/tng_led.h"

DAC8760 dac8760;

void dac8760_write_register_wo_crc(const uint8_t reg, const uint16_t data[4]) {
	uint8_t data_rx[3*4];
	uint8_t data_tx[3*4] = {
		reg, data[0] >> 8, data[0] & 0xFF,
		reg, data[1] >> 8, data[1] & 0xFF,
		reg, data[2] >> 8, data[2] & 0xFF,
		reg, data[3] >> 8, data[3] & 0xFF
	};

	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&dac8760.spi, data_tx, data_rx, 3*4, DAC8760_SPI_TIMEOUT);
	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_SET);
}

void dac8760_write_register(const uint8_t reg, const uint16_t data[4]) {
	uint8_t data_rx[4*4];
	uint8_t data_tx[4*4] = {
		reg, data[0] >> 8, data[0] & 0xFF, 0,
		reg, data[1] >> 8, data[1] & 0xFF, 0,
		reg, data[2] >> 8, data[2] & 0xFF, 0,
		reg, data[3] >> 8, data[3] & 0xFF, 0
	};
	data_tx[3]  = crc8(data_tx,      3);
	data_tx[7]  = crc8(data_tx + 4,  3);
	data_tx[11] = crc8(data_tx + 8,  3);
	data_tx[15] = crc8(data_tx + 12, 3);

	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&dac8760.spi, data_tx, data_rx, 4*4, DAC8760_SPI_TIMEOUT);
	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_SET);
}

void dac8760_read_register(const uint8_t read_reg, uint16_t *data) {
#if 0
	dac8760_write_register(DAC8760_REG_READ, read_reg);

	uint8_t data_rx[4] = {0};
	uint8_t data_tx[4] = {0};
	
	// Wait for at least 40ns between two cs (see 7.8 t_15 in DAC8760 datasheet)
	// One NOP should be about 15ns
	__NOP(); __NOP(); __NOP();
	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&dac8760.spi, data_tx, data_rx, 4, DAC8760_SPI_TIMEOUT);
	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_SET);

	return data_rx[2] | (data_rx[1] << 8);
#endif
}


void dac8760_enable_daisy_chain_and_crc(void) {
	// Bit 3 is daisy-chain enable in control register
	// and also happens to be crc enable in config register!
	uint16_t data[4] = {
		(1 << 3),
		(1 << 3),
		(1 << 3),
		(1 << 3)
	};

	// Enable daisy chain for times, each latching
	// the message is transfered one chip further.
	dac8760_write_register_wo_crc(DAC8760_REG_WRITE_CONTROL, data);
	dac8760_write_register_wo_crc(DAC8760_REG_WRITE_CONTROL, data);
	dac8760_write_register_wo_crc(DAC8760_REG_WRITE_CONTROL, data);
	dac8760_write_register_wo_crc(DAC8760_REG_WRITE_CONTROL, data);

	// Enable CRC
	dac8760_write_register_wo_crc(DAC8760_REG_WRITE_CONFIG, data);
}

uint16_t dac8760_get_dac_value(const uint8_t channel) {
	// TODO: Check range and check if voltage or current is configured
	return BETWEEN(0, SCALE(dac8760.voltage[channel], -10000, 10000, 0, 0xFFFF), 0xFFFF);
}

void dac8760_tick(void) {
	static uint32_t last_time = 0;
//	uint16_t status = dac8760_read_register(DAC8760_READ_STATUS);
//	logd("status: %b\n\r", status);

	uint16_t values[4] = {
		dac8760_get_dac_value(3),
		dac8760_get_dac_value(2),
		dac8760_get_dac_value(1),
		dac8760_get_dac_value(0),
	};
	dac8760_write_register(DAC8760_REG_WRITE_DAC, values);
	
	if(system_timer_is_time_elapsed_ms(last_time, 500)) {
		last_time = system_timer_get_ms();
		logd("values: %d %d %d %d\n\r", values[0], values[1], values[2], values[3]);
	}

	tng_led_channel_set(TNG_LED_VOLTAGE_CHANNEL_0, dac8760.voltage[0] > 0);
	tng_led_channel_set(TNG_LED_VOLTAGE_CHANNEL_1, dac8760.voltage[1] > 0);
	tng_led_channel_set(TNG_LED_VOLTAGE_CHANNEL_2, dac8760.voltage[2] > 0);
	tng_led_channel_set(TNG_LED_VOLTAGE_CHANNEL_3, dac8760.voltage[3] > 0);

	tng_led_channel_set(TNG_LED_CURRENT_CHANNEL_0, dac8760.voltage[0] > 0);
	tng_led_channel_set(TNG_LED_CURRENT_CHANNEL_1, dac8760.voltage[1] > 0);
	tng_led_channel_set(TNG_LED_CURRENT_CHANNEL_2, dac8760.voltage[2] > 0);
	tng_led_channel_set(TNG_LED_CURRENT_CHANNEL_3, dac8760.voltage[3] > 0);
}

void dac8760_init_spi(void) {
	// Enable clocks
	__HAL_RCC_SPI1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Configure CLK
	GPIO_InitTypeDef gpio_clk = {
		.Pin       = DAC8760_SPI_CLK_PIN,
		.Mode      = GPIO_MODE_AF_PP,
		.Pull      = GPIO_NOPULL,
		.Speed     = GPIO_SPEED_FREQ_HIGH,
		.Alternate = DAC8760_SPI_CLK_AF
	};
	HAL_GPIO_Init(DAC8760_SPI_CLK_PORT, &gpio_clk);

	// Configure MOSI
	GPIO_InitTypeDef gpio_mosi = {
		.Pin       = DAC8760_SPI_MOSI_PIN,
		.Mode      = GPIO_MODE_AF_PP,
		.Pull      = GPIO_NOPULL,
		.Speed     = GPIO_SPEED_FREQ_HIGH,
		.Alternate = DAC8760_SPI_MOSI_AF
	};
	HAL_GPIO_Init(DAC8760_SPI_MOSI_PORT, &gpio_mosi);

	// Configure MISO
	GPIO_InitTypeDef gpio_miso = {
		.Pin       = DAC8760_SPI_MISO_PIN,
		.Mode      = GPIO_MODE_AF_PP,
		.Pull      = GPIO_NOPULL,
		.Speed     = GPIO_SPEED_FREQ_HIGH,
		.Alternate = DAC8760_SPI_MISO_AF
	};
	HAL_GPIO_Init(DAC8760_SPI_MISO_PORT, &gpio_miso);

	// Configure CS
	GPIO_InitTypeDef gpio_cs = {
		.Pin       = DAC8760_SPI_CS_PIN,
		.Mode      = GPIO_MODE_OUTPUT_PP,
		.Pull      = GPIO_NOPULL,
		.Speed     = GPIO_SPEED_FREQ_HIGH,
	};
	HAL_GPIO_Init(DAC8760_SPI_CS_PORT, &gpio_cs);

	// Reset
	__HAL_RCC_SPI1_FORCE_RESET();
	__HAL_RCC_SPI1_RELEASE_RESET();

	dac8760.spi.Instance               = DAC8760_SPI_INSTANCE;
	dac8760.spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	dac8760.spi.Init.Direction         = SPI_DIRECTION_2LINES;
	dac8760.spi.Init.CLKPhase          = SPI_PHASE_1EDGE;
	dac8760.spi.Init.CLKPolarity       = SPI_POLARITY_LOW;
	dac8760.spi.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	dac8760.spi.Init.CRCPolynomial     = 7;
	dac8760.spi.Init.DataSize          = SPI_DATASIZE_8BIT;
	dac8760.spi.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	dac8760.spi.Init.NSS               = SPI_NSS_SOFT; 
	dac8760.spi.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
	dac8760.spi.Init.TIMode            = SPI_TIMODE_DISABLE;
	dac8760.spi.Init.Mode              = SPI_MODE_MASTER;	
	HAL_SPI_Init(&dac8760.spi);
}

void dac8760_init(void) {
	memset(&dac8760, 0, sizeof(DAC8760));

	dac8760_init_spi();

	// POR reset takes about 1ms according to datasheet
	system_timer_sleep_ms(10);

	// Write NOOP command (toggle CS pin without CLK changes)
	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_RESET);
	system_timer_sleep_ms(1);
	HAL_GPIO_WritePin(DAC8760_SPI_CS_PORT, DAC8760_SPI_CS_PIN, GPIO_PIN_SET);

	dac8760_enable_daisy_chain_and_crc();

	uint16_t config[4] = {
		(1 << 3) | (1 << 8) | ((0+1) << 9),
		(1 << 3) | (1 << 8) | ((0+1) << 9),
		(1 << 3) | (1 << 8) | ((0+1) << 9),
		(1 << 3) | (1 << 8) | ((0+1) << 9)
	};
	dac8760_write_register(DAC8760_REG_WRITE_CONFIG, config);

	uint16_t control[4] = {
		((1 << 12)) | 3 | (1 << 3),
		((1 << 12)) | 3 | (1 << 3),
		((1 << 12)) | 3 | (1 << 3),
		((1 << 12)) | 3 | (1 << 3)
	};
	dac8760_write_register(DAC8760_REG_WRITE_CONTROL, control);
}
