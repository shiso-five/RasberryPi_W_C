#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>

#define I2CBUS      1
#define MCP23017_ADDR 0x20
#define ADDR_IODIRA 0x00
#define ADDR_GPIOA  0x12
