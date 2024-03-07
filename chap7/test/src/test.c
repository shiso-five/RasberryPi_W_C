#include "../include/test.h"

int main(void){
  int i2cHandle;
  int adapter=I2CBUS;
  char fname[256];
  uint8_t buf[1024];

  memset(buf, 0, sizeof(buf));

  snprintf(fname, 255, "/dev/i2c-%d", adapter);
  if( (i2cHandle = open(fname, O_RDWR)) < 0){
    fprintf(stderr, "ERROR: cannot open() I2C handler\n");
    exit(1);
  }
  
  if( ioctl(i2cHandle, I2C_SLAVE, MCP23017_ADDR) < 0 ){
    fprintf(stderr, "ERROR: cannot ioctl()\n");
    exit(1);
  }

  buf[0]=ADDR_IODIRA;
  buf[1]=0x00;
  if( write(i2cHandle, buf, 2) != 2 ){
    fprintf(stderr, "ERROR: cannot write()\n");
    exit(1);        
  }

  while(1){
    buf[0]=ADDR_GPIOA;
    buf[1]=0xff;
    if( write(i2cHandle, buf, 2) != 2 ){
      fprintf(stderr, "ERROR: cannot write()\n");
      exit(1);        
    }
    sleep(1);

    buf[0]=ADDR_GPIOA;
    buf[1]=0x00;
    if( write(i2cHandle, buf, 2) != 2 ){
      fprintf(stderr, "ERROR: cannot write()\n");
      exit(1);        
    }
    sleep(1);    
  }

  close(i2cHandle);
  
  return 0;
}
