#include "../include/TMP102.h"

float ReadTemp(int handle){
  char buf[1024]; 
  int temp;
  float deg, lsb=0.0625; 
  
  //get temparature from TMP102
  if( ioctl(handle, I2C_SLAVE, TMP102_ADDR) < 0 ){
    fprintf(stderr, "ERROR: cannot ioctl() \n");
    exit(1);
  }
  buf[0] = 0x00;
  if( write(handle, buf, 1) != 1 ){
    fprintf(stderr, "ERROR: cannot write()\n");
  }
  read(handle, buf, 2);
  temp = (buf[0]<<4) + (buf[1]>>4);
  if(temp > 0x7ff){
    temp = (~temp) & 0xffff;
    temp++;
    deg = temp * lsb;
  }
  else{
    deg = temp * lsb;
  }

  return deg;
}
