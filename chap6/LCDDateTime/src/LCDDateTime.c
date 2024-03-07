#include "../include/LCDDateTime.h"

int main(void){
  struct LCD lcd;
  char currentDate[16], currentTime[12];
  struct tm *timeInfo;
  time_t timer;

  LCDInit(&lcd);
  LCDDispOn(&lcd, 1, 0, 0);

  while(1){
    time(&timer);
    timer += 9*3600;
    timeInfo = gmtime(&timer);

    strftime(currentDate, 256, "20%y-%m-%d", timeInfo);
    strftime(currentTime, 256, "%Hh %Mm %Ss", timeInfo);

    LCDGoToXY(&lcd, 0, 0);
    LCDPrint(&lcd, currentDate);

    LCDGoToXY(&lcd, 0, 1);
    LCDPrint(&lcd, currentTime);

    time_sleep(0.5);
  }
  
  return 0;
}
