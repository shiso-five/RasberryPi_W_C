#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pigpio.h>

#define SSR 11

int main(void){
  char str[1024];
  
  gpioInitialise();
  gpioSetMode(SSR, PI_OUTPUT);

  gpioWrite(SSR, 1);

  while(1){
    scanf("%s", str);
    if(!strcmp(str, "quit")){
      break;
    }
    else{
      continue;
    }
  }

  gpioWrite(SSR, 0);

  return 0;
}
