#include "../include/I2C_LCD_W_TMP102.h"

int main(void){
  struct I2CLCD lcd;
  struct tm *timeInfo;
  time_t timer;
  char rowUpper[256], rowLower[256], currentDate[16], currentTime[12], buf[1024];
  int temp;
  float deg, lsb=0.0625;  
  
  I2CLCDInit(&lcd);
  I2CLCDDispOn(&lcd, 1, 0, 0);

  while(1){
    memset(rowUpper, '\0', sizeof(rowUpper));
    memset(rowLower, '\0', sizeof(rowLower));

    time(&timer);
    timer += 9*3600;
    timeInfo = gmtime(&timer);

    strftime(currentDate, 16, "20%y-%m-%d",  timeInfo);
    strftime(currentTime, 12, "%Hh %Mm %Ss", timeInfo);

    if( ioctl(lcd.i2cHandle, I2C_SLAVE, TMP102_ADDR) < 0 ){
      fprintf(stderr, "ERROR: cannot ioctl() \n");
      exit(1);
    }
    buf[0] = 0x00;
    if( write(lcd.i2cHandle, buf, 1) != 1 ){
      fprintf(stderr, "ERROR: cannot write()\n");
    }
    read(lcd.i2cHandle, buf, 2);
    temp = (buf[0]<<4) + (buf[1]>>4);
    if(temp > 0x7ff){
      temp = (~temp) & 0xffff;
      temp++;
      deg = temp * lsb;
    }
    else{
      deg = temp * lsb;
    }    

    if( ioctl(lcd.i2cHandle, I2C_SLAVE, lcd.slaveAddr) < 0 ){
      fprintf(stderr, "ERROR: cannot ioctl() \n");
      exit(1);
    }    

    snprintf(rowUpper, 256, "%s %3.1fC", currentDate, deg);
    snprintf(rowLower, 256, "%s", currentTime);    

    I2CLCDGoToXY(&lcd, 0, 0);
    I2CLCDPrint(&lcd, rowUpper);

    I2CLCDGoToXY(&lcd, 0, 1);
    I2CLCDPrint(&lcd, rowLower);

    usleep(400000);
  }
  
  return 0;
}
