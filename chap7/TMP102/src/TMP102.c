#include "../include/TMP102.h"

int main(void){
  int i2cHandle, temp;
  int adapter=I2CBUS;
  char fname[256], buf[1024];
  float deg, LSB=0.0625;

  snprintf(fname, 255, "/dev/i2c-%d", adapter);
  if( (i2cHandle = open(fname, O_RDWR)) < 0 ){
    fprintf(stderr, "ERROR: cannot open() I2C handler\n");
    exit(1);
  }

  if( ioctl(i2cHandle, I2C_SLAVE, TMP102_ADDR) < 0 ){
    fprintf(stderr, "ERROR: cannot ioctl() \n");
    exit(1);
  }
  
  while(1){
    buf[0] = 0x00;
    if( write(i2cHandle, buf, 1) != 1 ){
      fprintf(stderr, "ERROR: cannot write()\n");
    }

    read(i2cHandle, buf, 2);
    temp = (buf[0]<<4) + buf[1];

    if(temp > 0x7ff){
      temp = (~temp) & 0xffff;
      temp++;
      deg = temp * LSB;
    }
    else{
      deg = temp * LSB;
    }

    printf("temperature = %+5.2f\n", deg);
    sleep(1);
  }
  
  return 0;
}
