/* tng-ao-4u-4
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * dac8760.h: Driver for DAC8760 DAC 
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

#ifndef DAC8760_H
#define DAC8760_H

#include "configs/config.h"

#include <stdint.h>

#define DAC8760_VOLTAGE_NUM 4
#define DAC8760_CURRENT_NUM 4

typedef struct {
    int32_t voltage[DAC8760_VOLTAGE_NUM];
    int32_t current[DAC8760_CURRENT_NUM];

    SPI_HandleTypeDef spi;
} DAC8760;

extern DAC8760 dac8760;

void dac8760_tick(void);
void dac8760_init(void);

#define DAC8760_REG_NOP            0x00
#define DAC8760_REG_WRITE_DAC      0x01
#define DAC8760_REG_READ           0x02
#define DAC8760_REG_WRITE_CONTROL  0x55
#define DAC8760_REG_WRITE_RESET    0x56
#define DAC8760_REG_WRITE_CONFIG   0x57
#define DAC8760_REG_WRITE_CAL_GAIN 0x58
#define DAC8760_REG_WRITE_CAL_ZERO 0x59
#define DAC8760_REG_RESET_WATCHDOG 0x95

#define DAC8760_CONFIG_WDPD(w)       ((w) << 0)
#define DAC8760_CONFIG_WDEN          (1 << 2)
#define DAC8760_CONFIG_CRCEN         (1 << 3)
#define DAC8760_CONFIG_HARTEN        (1 << 4)
#define DAC8760_CONFIG_APD           (1 << 7)
#define DAC8760_CONFIG_DUAL_OUTEN    (1 << 8)
#define DAC8760_CONFIG_IOUT_RANGE(r) ((r) << 9)

#define DAC8760_CONTROL_RANGE(r)     ((r) << 0)
#define DAC8760_CONTROL_DCEN         (1 << 3)
#define DAC8760_CONTROL_SREN         (1 << 4)
#define DAC8760_CONTROL_SRSTEP(s)    ((s) << 5)
#define DAC8760_CONTROL_SRCLK(s)     ((s) << 8)
#define DAC8760_CONTROL_OUTEN        (1 << 12)
#define DAC8760_CONTROL_REXT         (1 << 13)
#define DAC8760_CONTROL_OVR          (1 << 14)
#define DAC8760_CONTROL_CLRSEL       (1 << 15)

#define DAC8760_READ_STATUS          0b000000
#define DAC8760_READ_DAC             0b000001
#define DAC8760_READ_CONTROL         0b000010
#define DAC8760_READ_CONFIG          0b001011
#define DAC8760_READ_CAL_GAIN        0b010011
#define DAC8760_READ_CAL_ZERO        0b010111

#endif
