#include "../include/LCDSeconds.h"

int main(void){
  struct LCD lcd;
  char str[1024];
  int count=0;

  LCDInit(&lcd);

  LCDDispOn(&lcd, 1, 0, 0);

  sprintf(str, "SECONDS:");
  LCDPrint(&lcd, str);
  while(1){
    LCDGoToXY(&lcd, 0, 1);
    count++;
    time_sleep(1);
    sprintf(str, "%d", count);
    LCDPrint(&lcd, str);    
  }

  return 0;
}
