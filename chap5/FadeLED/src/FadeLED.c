#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pigpio.h>

#define ON    1
#define OFF   0
#define PIN   11

void Configure(void);

int main(void){
  int k;
  
  gpioInitialise();
  Configure();

  gpioSetPWMfrequency(PIN, 50);
  printf("PWM range is %d\n", gpioGetPWMrange(PIN));

  while(1){
    for(k=0;k<256;k++){
      gpioPWM(PIN, k);
      time_sleep(0.025);
    }
    for(k=0;k<256;k++){
      gpioPWM(PIN, 255-k);
      time_sleep(0.025);
    }    
  }
  
  return 0;
}

void Configure(void){
  gpioSetMode(PIN, PI_OUTPUT);
  gpioWrite(PIN, OFF);
  return;  
}
