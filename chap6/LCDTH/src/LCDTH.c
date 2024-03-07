#include "../include/LCDTH.h"

int main(void){
  struct LCD lcd;
  char currentDate[16], currentTime[12], rowUpper[256], rowLower[256];
  struct tm *timeInfo;
  time_t timer;
  int temp, hum;

  LCDInit(&lcd);
  LCDDispOn(&lcd, 1, 0, 0);

  while(1){
    memset(rowUpper, '\0', sizeof(rowUpper));
    memset(rowLower, '\0', sizeof(rowLower));
    memset(&temp,        0, sizeof(temp));
    memset(&hum,         0, sizeof(hum));        
    
    time(&timer);
    timer += 9*3600;
    timeInfo = gmtime(&timer);

    ReadDHT11(&temp, &hum);

    strftime(currentDate, 256, "20%y-%m-%d", timeInfo);
    strftime(currentTime, 256, "%Hh %Mm %Ss", timeInfo);

    sprintf(rowUpper, "%s  %3dC", currentDate, temp);
    sprintf(rowLower, "%s %3d%%", currentTime, hum);    

    LCDGoToXY(&lcd, 0, 0);
    LCDPrint(&lcd, rowUpper);

    LCDGoToXY(&lcd, 0, 1);
    LCDPrint(&lcd, rowLower);

    time_sleep(0.4);
  }
  
  return 0;
}
