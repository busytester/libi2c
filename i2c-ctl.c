/*
 * i2c-ctl: demo program for i2c read/write
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <i2c-io.h>

void print_usage(char *name)
{
	printf("usage:	%s <adapter> r <address> <register> <num-bytes>\n",
			name);
	printf("\t%s <adapter> w <address> <register> <b1> [b2] [b3] ...\n",
			name);
}

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int i;
	struct stat st;
	unsigned int addr, reg, nb;
	uint8_t *buf;

	if (argc < 6 || (argv[2][0] != 'r' && argv[2][0] != 'w')) {
		print_usage(argv[0]);
		return 0;
	}

	if (sscanf(argv[3], "%x", &addr) != 1) {
		printf("error: invalid address\n");
		print_usage(argv[0]);
		return 1;
	}

	if (sscanf(argv[4], "%x", &reg) != 1) {
		printf("error: invalid register\n");
		print_usage(argv[0]);
		return 2;
	}

	if (stat("/sys/class/i2c-dev", &st)) {
		printf("error: i2c-dev not loaded\n");
		return 3;
	}

	fd = i2c_open(argv[1]);
	if (fd < 0)
		return 4;

	if (argv[2][0] == 'r') {
		if (sscanf(argv[5], "%u", &nb) != 1) {
			fprintf(stderr, "error: invalid number of bytes\n");
			print_usage(argv[0]);
			close(fd);
			return 5;
		}

		if (nb < 1) {
			fprintf(stderr, "error: read at least one byte\n");
			print_usage(argv[0]);
			close(fd);
			return 5;
		}

		buf = malloc(nb);
		if (!buf) {
			perror("malloc");
			close(fd);
			return 6;
		}

		ret = i2c_read(fd, addr, reg, buf, nb);
		if (ret < 0) {
			printf("error: %d\n", ret);
			free(buf);
			close(fd);
			return 7;
		}

		for (i = 1; i < nb; i++)
			printf("%02x ", buf[i]);
		printf("\n");
		free(buf);
	} else if (argv[2][0] == 'w') {
		buf = malloc(argc - 5);
		if (!buf) {
			perror("malloc");
			close(fd);
			return 6;
		}

		for (i = 0; i < argc - 5; i++) {
			if (sscanf(argv[i+5], "%x",
					(unsigned int *)&buf[i]) != 1) {
				printf("error: argument %d invalid\n", i+5);
				free(buf);
				close(fd);
				return 8;
			}
		}

		ret = i2c_write(fd, addr, reg, buf, argc - 5);
		if (ret < 0) {
			printf("error: %d\n", ret);
			free(buf);
			close(fd);
			return 7;
		}
		free(buf);
	}

	close(fd);
	return 0;
}
