/* tng-ao-4u-4i
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_dac8760.h: Configuration DAC8760 DAC
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

#ifndef CONFIG_DAC8760_H
#define CONFIG_DAC8760_H

#include "configs/config.h"

#define DAC8760_LED_R_PIN          GPIO_PIN_8
#define DAC8760_LED_R_PORT         GPIOA
#define DAC8760_LED_G_PIN          GPIO_PIN_9
#define DAC8760_LED_G_PORT         GPIOA
#define DAC8760_LED_B_PIN          GPIO_PIN_10
#define DAC8760_LED_B_PORT         GPIOA

#define DAC8760_LED_0_PIN          GPIO_PIN_2
#define DAC8760_LED_0_PORT         GPIOA
#define DAC8760_LED_1_PIN          GPIO_PIN_3
#define DAC8760_LED_1_PORT         GPIOA
#define DAC8760_LED_2_PIN          GPIO_PIN_4
#define DAC8760_LED_2_PORT         GPIOA
#define DAC8760_LED_3_PIN          GPIO_PIN_5
#define DAC8760_LED_3_PORT         GPIOA
#define DAC8760_LED_4_PIN          GPIO_PIN_6
#define DAC8760_LED_4_PORT         GPIOA
#define DAC8760_LED_5_PIN          GPIO_PIN_7
#define DAC8760_LED_5_PORT         GPIOA
#define DAC8760_LED_6_PIN          GPIO_PIN_0
#define DAC8760_LED_6_PORT         GPIOB
#define DAC8760_LED_7_PIN          GPIO_PIN_1
#define DAC8760_LED_7_PORT         GPIOB

#define DAC8760_AIN0_PIN           GPIO_PIN_0
#define DAC8760_AIN0_PORT          GPIOA
#define DAC8760_ADC_RESET_PIN      GPIO_PIN_1
#define DAC8760_ADC_RESET_PORT     GPIOA
#define DAC8760_PWR_GOOD_PIN       GPIO_PIN_8
#define DAC8760_PWR_GOOD_PORT      GPIOB

#define DAC8760_SPI_CS_PIN         GPIO_PIN_15
#define DAC8760_SPI_CS_PORT        GPIOA
#define DAC8760_SPI_CS_AF          GPIO_AF0_SPI1
#define DAC8760_SPI_CLK_PIN        GPIO_PIN_3
#define DAC8760_SPI_CLK_PORT       GPIOB
#define DAC8760_SPI_CLK_AF         GPIO_AF0_SPI1
#define DAC8760_SPI_MISO_PIN       GPIO_PIN_4
#define DAC8760_SPI_MISO_PORT      GPIOB
#define DAC8760_SPI_MISO_AF        GPIO_AF0_SPI1
#define DAC8760_SPI_MOSI_PIN       GPIO_PIN_5
#define DAC8760_SPI_MOSI_PORT      GPIOB
#define DAC8760_SPI_MOSI_AF        GPIO_AF0_SPI1
#define DAC8760_SPI_INSTANCE       SPI1
#define DAC8760_SPI_TIMEOUT        1000

#endif
