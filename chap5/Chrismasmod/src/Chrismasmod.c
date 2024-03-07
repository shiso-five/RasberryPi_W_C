#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pigpio.h>

#define ON    1
#define OFF   1
#define NLEDS 8

int LEDs[] = {11, 9, 10, 22, 27, 17, 3, 2};

void Configure(void);
void Display(unsigned int, unsigned int);

int main(void){
  srand((unsigned int)time(NULL));
  printf("RAND_MAX = %u\n", RAND_MAX);

  unsigned int ran;

  gpioInitialise();
  Configure();

  while(1){
    ran = rand();
    Display(ran, NLEDS);
    time_sleep(0.5);
  }
  
  gpioTerminate();

  return 0;
}

void Configure(void){
  int k;
  for(k=0;k<NLEDS;k++){
    gpioSetMode(LEDs[k], PI_OUTPUT);
    gpioWrite(LEDs[k], OFF);
  }
  return;
}  

void Display(unsigned int No, unsigned int L){

  unsigned int i, j, m, p, r;

  m = L - 1;
  for(i=0;i<L;i++){
    j = 1;
    for(p=0;p<m;p++){
      j *= 2;
    }
    r = No & j;
    if(r>0){
      r=1;
    }
    gpioWrite(LEDs[i], r);
    m--;
  }
  
  return;
}
