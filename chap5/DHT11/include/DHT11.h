#include <stdio.h>
#include <pigpio.h>

#define DHT_PIN 11
#define ON      1
#define OFF     0
#define HIGH    1
#define LOW     0

//mode must be HIGH or LOW, if success, returns 0, otherwise 1.
//if mode == HIGH, waits for leading egde.
//when mode == HIGH and pin is HIGH, returns 0 soon.
//these behaviors are same when mode == LOW
//wait for maximum 255 us.
int WaitEdge(int); 

int ReadDHT11(int*, int*);

