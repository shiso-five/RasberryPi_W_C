#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

#include <pigpio.h>

#include "../../../lib/include/i2clcd.h"
#include "../../../lib/include/TMP102.h"

#define SSR 11
