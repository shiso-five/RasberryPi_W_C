#include "../include/HelloWorld.h"

int main(void){
  struct LCD lcd;
  char str[1024];
  
  LCDInit(&lcd);

  LCDGoToXY(&lcd, 2, 0);
  sprintf(str, "Hello World!");  
  LCDPrint(&lcd, str);
  LCDGoToXY(&lcd, 5, 1);
  sprintf(str, "S.Ogio");  
  LCDPrint(&lcd, str);
//  LCDGoToXY(&lcd, 2, 0);
//  sprintf(str, "Raspberry Pi");
//  LCDPrint(&lcd, str);
//  LCDGoToXY(&lcd, 4, 1);
//  sprintf(str, "Computer");  
//  LCDPrint(&lcd, str);    

  //  LCDTerm(&lcd);
  
  return 0;
}
