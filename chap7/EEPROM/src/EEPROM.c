#include "../include/EEPROM.h"

int main(void){
  int i2cHandle;
  int adapter=I2CBUS;
  char fname[256];
  //  char wmsg[] = {'A', 'B', 'C', 'D'};
  char wmsg[] = "sayaka";
  char rmsg[1024];

  snprintf(fname, 255, "/dev/i2c-%d", adapter);
  if( (i2cHandle = open(fname, O_RDWR)) < 0 ){
    fprintf(stderr, "ERROR: cannot open() I2C handler\n");
    exit(1);
  }

  if( ioctl(i2cHandle, I2C_SLAVE, _24LC256_ADDR) < 0 ){
    fprintf(stderr, "ERROR: cannot ioctl() \n");
    exit(1);
  }

  Write24LC256(i2cHandle, 0x1000, wmsg, strlen(wmsg));
  Read24LC256(i2cHandle, 0x1000, rmsg, strlen(wmsg));

  rmsg[strlen(wmsg)] = '\0';
 
  printf("message: %s\n", rmsg);
  
  return 0;
}

void Write24LC256(int handle, uint16_t loc, char *data, int len){
  int i, ret;
  uint8_t addr[2], buf[1024];
  
  addr[0] = ((loc & 0xff00) >> 8); //address higher 8-bit
  addr[1] = (loc & 0x00ff);        //address lower 8-bit
  
  for(i=0;i<len;i++){    
    buf[0] = addr[0];
    buf[1] = addr[1] + i;
    buf[2] = data[i];
    if( (ret = write(handle, buf, 3)) != 3 ){
      fprintf(stderr, "ERROR: cannot write() loop: %d, ret: %d\n", i, ret);
      exit(1);
    }
    usleep(10000);
  }

  return;
}
void Read24LC256 (int handle, uint16_t loc, char *data, int len){
  int i;
  uint8_t addr[2], buf[1024];

  addr[0] = ((loc & 0xff00) >> 8); //address higher 8-bit
  addr[1] = (loc & 0x00ff);        //address lower 8-bit  
  
  buf[0] = addr[0];
  buf[1] = addr[1];  
  write(handle, buf, 2);

  for(i=0;i<len;i++){
    read(handle, buf, 1);
    data[i] = buf[0];
  }  
    
  return;
}
