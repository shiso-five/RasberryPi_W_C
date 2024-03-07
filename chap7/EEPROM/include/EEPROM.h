#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#define I2CBUS      1
#define _24LC256_ADDR 0x50

void Write24LC256(int, uint16_t, char*, int);
void Read24LC256 (int, uint16_t, char*, int);
