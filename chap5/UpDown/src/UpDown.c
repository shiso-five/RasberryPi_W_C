#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <pigpio.h>

#define ON     1
#define OFF    0
#define NLEDS  8
#define BUTTON 26
#define UP     0
#define DOWN   1

int LEDs[] = {11, 9, 10, 22, 27, 17, 3, 2};

void Configure(void);
void Display(unsigned int, unsigned int);

int main(void){

  char count, buttonState;
  
  gpioInitialise();
  Configure();

  count = 0;
  buttonState = UP;
  while(1){
    Display((unsigned int)count, NLEDS);
    buttonState = gpioRead(BUTTON);
    
    if(buttonState == UP){
      printf("STATE IS UP\n");
      if(count==255){
	count = 0;
      }
      else{
	count++;
      }
    }
    else if(buttonState == DOWN){
      printf("STATE IS DOWN\n");      
      if(count==0){
	count = 255;
      }
      else{
	count--;
      }
    }
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
  gpioSetMode(BUTTON, PI_INPUT);
  
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
