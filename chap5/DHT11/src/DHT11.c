#include "../include/DHT11.h"

int main(void){
  int temp, hum;

  gpioInitialise();
  time_sleep(1);

  while(1){
//    if(!ReadDHT11(&temp, &hum)){
//      printf("T=%u C, H=%u %%\n", temp, hum);
//    }
    ReadDHT11(&temp, &hum);
    printf("T=%d C, H=%d %%\n", temp, hum);
    time_sleep(5);
  }
  
  return 0;
}

int WaitEdge(int mode){
  int counter;

  while( gpioRead(DHT_PIN) == mode ){
    counter++;
    gpioDelay(1);
    if(counter==255){
      return 1;
    }
  }
  return 0;
}
int ReadDHT11(int *temp, int *hum){
  int i, indx, res, counter;
  int data[5];  
  
  for(i=0;i<5;i++){
    data[i] = 0;
  }

  gpioSetMode(DHT_PIN, PI_OUTPUT);
  gpioWrite(DHT_PIN, LOW);
  time_sleep(0.018); //wait 18 ms
  gpioWrite(DHT_PIN, HIGH);
  gpioDelay(40);     //wait 40 us
  gpioSetMode(DHT_PIN, PI_INPUT);

  res  = WaitEdge(0);
  res += WaitEdge(1);
  if(res){
    fprintf(stderr, "ERROR: cannot initialize communication with DHT11\n");
    return 1;
  }
    
  indx=0;
  for(i=0;i<80;i++){

    counter = 0;
    if(WaitEdge(0) == 1){
      fprintf(stderr, "ERROR: NO valid trailing edge\n");
      break;
    }
    while(gpioRead(DHT_PIN) == 1){
      counter++;
      gpioDelay(1);
      if(counter == 255){
	//	fprintf(stderr, "ERROR: timeout for NO valid logical signal\n");		
	break;
      }
    }
    if(indx < 40){
      data[indx/8] <<= 1;
      if(counter > 30){
	data[indx/8]  |= 1;
      }
    }

    //    printf("indx = %d counter = %d\n", indx, counter);
    indx++;    
  }

  //checksum
  if( (indx>=40) && (data[4] = ((data[0]+data[1]+data[2]+data[3]) & 0xff)) ){
    *temp = data[2];
    *hum  = data[0];
  }
  else{
    *temp = -1;
    *hum  = -1;    
  }
  
  
  return 0;
}
