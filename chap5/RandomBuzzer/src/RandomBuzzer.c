#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pigpio.h>

#define ON  1
#define OFF 0
#define BUZ 11 

void Configure(void);

int main(void){
  int freq;
  srand((unsigned int)time(NULL));

  gpioInitialise();
  Configure();

  gpioPWM(BUZ, 128);

  while(1){
    freq = rand() % 901 + 100;    
    gpioSetPWMfrequency(BUZ, freq);
    time_sleep(1);
  }
  
  return 0;
}

void Configure(void){
  gpioSetMode(BUZ, PI_OUTPUT);
  gpioWrite(BUZ, OFF);

  return;
}  
