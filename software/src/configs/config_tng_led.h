/* tng-ao-4u-4i
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_led.h: LED driver configuration for TNG DO8
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

#ifndef CONFIG_LED_H
#define CONFIG_LED_H

#include "configs/config.h"

#define TNG_LED_STATUS_R_PIN        GPIO_PIN_8
#define TNG_LED_STATUS_R_PORT       GPIOA
#define TNG_LED_STATUS_G_PIN        GPIO_PIN_9
#define TNG_LED_STATUS_G_PORT       GPIOA
#define TNG_LED_STATUS_B_PIN        GPIO_PIN_10
#define TNG_LED_STATUS_B_PORT       GPIOA

#define TNG_LED_CHANNEL_NUM         8

#define TNG_LED_CHANNEL_0_PIN       GPIO_PIN_2
#define TNG_LED_CHANNEL_0_PORT      GPIOA
#define TNG_LED_CHANNEL_1_PIN       GPIO_PIN_3
#define TNG_LED_CHANNEL_1_PORT      GPIOA
#define TNG_LED_CHANNEL_2_PIN       GPIO_PIN_4
#define TNG_LED_CHANNEL_2_PORT      GPIOA
#define TNG_LED_CHANNEL_3_PIN       GPIO_PIN_5
#define TNG_LED_CHANNEL_3_PORT      GPIOA
#define TNG_LED_CHANNEL_4_PIN       GPIO_PIN_6
#define TNG_LED_CHANNEL_4_PORT      GPIOA
#define TNG_LED_CHANNEL_5_PIN       GPIO_PIN_7
#define TNG_LED_CHANNEL_5_PORT      GPIOA
#define TNG_LED_CHANNEL_6_PIN       GPIO_PIN_0
#define TNG_LED_CHANNEL_6_PORT      GPIOB
#define TNG_LED_CHANNEL_7_PIN       GPIO_PIN_1
#define TNG_LED_CHANNEL_7_PORT      GPIOB

#define TNG_LED_VOLTAGE_CHANNEL_0   TNG_LED_CHANNEL_0
#define TNG_LED_VOLTAGE_CHANNEL_1   TNG_LED_CHANNEL_2
#define TNG_LED_VOLTAGE_CHANNEL_2   TNG_LED_CHANNEL_4
#define TNG_LED_VOLTAGE_CHANNEL_3   TNG_LED_CHANNEL_6
#define TNG_LED_CURRENT_CHANNEL_0   TNG_LED_CHANNEL_1
#define TNG_LED_CURRENT_CHANNEL_1   TNG_LED_CHANNEL_3
#define TNG_LED_CURRENT_CHANNEL_2   TNG_LED_CHANNEL_5
#define TNG_LED_CURRENT_CHANNEL_3   TNG_LED_CHANNEL_7

#endif
