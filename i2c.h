/*
 * i2c interface for userspace
 *
 * (c) 2010 Andrey Yurovsky <yurovsky@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301 USA
 */
#ifndef __I2C_LIB_H__
#define __I2C_LIB_H__
#include <stdint.h>

int i2c_write(int fd, uint8_t addr, uint8_t reg, uint8_t *buf,
		unsigned int nb);

int i2c_read(int fd, uint8_t addr, uint8_t reg, uint8_t *buf, unsigned int nb);

int i2c_open(char *adapter);
#endif /* __I2C_LIB_H__ */
