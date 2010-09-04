/*
 * i2c interface for userspace
 *
 * (c) 2010 Andrey Yurovsky <yurovsky@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef __I2C_LIB_H__
#define __I2C_LIB_H__
#include <stdint.h>

int i2c_write(int fd, uint8_t addr, uint8_t reg, uint8_t *buf,
		unsigned int nb);

int i2c_read(int fd, uint8_t addr, uint8_t reg, uint8_t *buf, unsigned int nb);

int i2c_open(char *adapter);
#endif /* __I2C_LIB_H__ */
