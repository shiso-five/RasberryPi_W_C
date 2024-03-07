#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define ON  1
#define OFF 0

//int LEDs[] = {27, 17, 3, 2};
int LEDs[] = {11, 9, 10, 22};

void Configure(void);

int main(void){
  int i;
  
  printf("Rotete LEDs\n");
  gpioInitialise();
  Configure();

  while(1){
    for(i=0;i<4;i++){
      gpioWrite(LEDs[i], ON);
      time_sleep(0.5);
      gpioWrite(LEDs[i], OFF);
      time_sleep(0.1);      
    }
  }
  
  return 0;
}

void Configure(void){
  int k;
  for(k=0;k<4;k++){
    gpioSetMode(LEDs[k], PI_OUTPUT);
    gpioWrite(LEDs[k], OFF);
  }
  return;
}
