#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pigpio.h>

#define ON  1
#define OFF 0
#define BUZ 11

void Configure(void);

int main(void){
  gpioInitialise();
  Configure();

  while(1){
    gpioWrite(BUZ, ON);
    time_sleep(0.5);
    gpioWrite(BUZ, OFF);
    time_sleep(0.5);    
  }

  gpioWrite(BUZ, OFF);  
  gpioTerminate();
  
  return 0;
}

void Configure(void){
  gpioSetMode(BUZ, PI_OUTPUT);
  gpioWrite(BUZ, OFF);

  return;
}  
