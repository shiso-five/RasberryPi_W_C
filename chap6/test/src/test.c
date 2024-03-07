#include "../include/test.h"

int main(void){
  struct LCD lcd;
  char str[1024];
  char x[256],y[256];
  
  LCDInit(&lcd);
  
  while(1){
    printf(">");
    scanf("%s", str);
    if(!strcmp(str, "quit")){
      break;
    }
    else if(!strcmp(str, "clear")){
      LCDClear(&lcd);
    }
    else if(!strcmp(str, "home")){
      LCDHome(&lcd);
    }        
    else if(!strcmp(str, "dr")){
      LCDShift(&lcd, 1, 1);      
    }
    else if(!strcmp(str, "dl")){
      LCDShift(&lcd, 1, 0);
    }
    else if(!strcmp(str, "cr")){
      LCDShift(&lcd, 0, 1);      
    }
    else if(!strcmp(str, "cl")){
      LCDShift(&lcd, 0, 0);
    }
    else if(str[0]=='0'&&str[1]=='x'){
      LCDWrite(&lcd, (uint8_t)strtol(str+2, NULL, 16), 1);
    }
    else if(str[0]=='0'&&str[1]=='b'){
      LCDWrite(&lcd, (uint8_t)strtol(str+2, NULL, 2), 1);
    }
    else if( str == strstr(str, "print") ){
      LCDPrint(&lcd, str+5);
    }
    else if( str == strstr(str, "setcgram") ){
      LCDSetCGRAMAddr(&lcd, (uint8_t)strtol(str+8, NULL, 16));
    }    
    else if( str == strstr(str, "setddram") ){
      LCDSetDDRAMAddr(&lcd, (uint8_t)strtol(str+8, NULL, 16));      
    }
    else if( !strcmp(str, "goto") ){
      printf("x?>");
      scanf("%s", x);
      printf("y?>");
      scanf("%s", y);
      LCDGoToXY(&lcd, (uint8_t)strtol(x,NULL,10), (uint8_t)strtol(y,NULL,10));
    }    
    else{
      LCDPutChar(&lcd, str[0]);
    }    
  }
  printf("\n");
  
  LCDTerm(&lcd);
  
  return 0;
}
