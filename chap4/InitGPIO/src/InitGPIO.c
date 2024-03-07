#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define LED 2

int main(void){
  gpioInitialise();  
  gpioTerminate();
  return 0;
}
