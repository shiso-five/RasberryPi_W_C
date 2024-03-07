#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <pigpio.h>

#define HTTPPORT      54321
#define BUFFSIZE      1024
#define LARGEBUFFSIZE 65536
#define ON            1
#define OFF           0
//#define LED0          2
//#define LED1          3
//#define LED2          17
//#define LED3          27
//#define LED4          22
//#define LED5          10
//#define LED6          9
//#define LED7          11
#define NLEDS         8
#define BUZ           26

int LEDs[] = {2, 3, 17, 27, 22, 10, 9, 11};

int  httpd(int, struct sockaddr_in, char *);
int  SendErrMsg2Clnt(int, char*);
void Configure(void);
void Display(unsigned int, unsigned int);

int main(void){
  int servSock, clntSock, num=0;
  struct sockaddr_in servAddr, clntAddr;
  unsigned int clntAddrLen;
  char urlPara[BUFFSIZE];

  gpioInitialise();
  Configure();

  if( (servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ){
    fprintf(stderr, "ERROR: socket() failed\n");
  }

  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family      = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port        = htons(HTTPPORT);
  if( bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0 ){
    fprintf(stderr, "bind() failed\n");
    return 1;
  }
  
  if( listen(servSock, 5) < 0){
    fprintf(stderr, "listen() failed\n");
    return 1;
  }

  for(;;){
    clntAddrLen = sizeof(clntAddr);
    if( (clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &clntAddrLen)) < 0 ){
      fprintf(stderr, "ERROR: accept() failed\n");
      break;
    }
    httpd(clntSock, clntAddr, urlPara);
    if     ( strstr(urlPara, "LED0=ON" ) ) gpioWrite(LEDs[0], ON );
    else if( strstr(urlPara, "LED0=OFF") ) gpioWrite(LEDs[0], OFF);      
    else if( strstr(urlPara, "LED1=ON" ) ) gpioWrite(LEDs[1], ON );      
    else if( strstr(urlPara, "LED1=OFF") ) gpioWrite(LEDs[1], OFF);
    else if( strstr(urlPara, "LED2=ON" ) ) gpioWrite(LEDs[2], ON );
    else if( strstr(urlPara, "LED2=OFF") ) gpioWrite(LEDs[2], OFF);      
    else if( strstr(urlPara, "LED3=ON" ) ) gpioWrite(LEDs[3], ON );      
    else if( strstr(urlPara, "LED3=OFF") ) gpioWrite(LEDs[3], OFF);
    else if( strstr(urlPara, "LED4=ON" ) ) gpioWrite(LEDs[4], ON );
    else if( strstr(urlPara, "LED4=OFF") ) gpioWrite(LEDs[4], OFF);      
    else if( strstr(urlPara, "LED5=ON" ) ) gpioWrite(LEDs[5], ON );      
    else if( strstr(urlPara, "LED5=OFF") ) gpioWrite(LEDs[5], OFF);
    else if( strstr(urlPara, "LED6=ON" ) ) gpioWrite(LEDs[6], ON );
    else if( strstr(urlPara, "LED6=OFF") ) gpioWrite(LEDs[6], OFF);      
    else if( strstr(urlPara, "LED7=ON" ) ) gpioWrite(LEDs[7], ON );      
    else if( strstr(urlPara, "LED7=OFF") ) gpioWrite(LEDs[7], OFF);
    else if( strstr(urlPara, "BUZ=ON"  ) ) gpioWrite(BUZ,  ON );      
    else if( strstr(urlPara, "BUZ=OFF" ) ) gpioWrite(BUZ,  OFF);
    else if( strstr(urlPara, "EXIT=EXIT" ) ) break;
    else if( strstr(urlPara, "num"     ) ){
      //      printf("\n urlPara = '%s' and num is %d\n", urlPara, atoi(urlPara+4));
      num = atoi(urlPara+4);
      if( 0<=num && num<256 ){
	Display(num, NLEDS);
      }
      else{
	fprintf(stderr, "ERROR: num is too small or too large.\n");
      }
    }

    close(clntSock);
  }

  close(servSock);
  
  return 0;
}

int httpd(int clntSock, struct sockaddr_in clntAddr, char* urlPara){
  char recvStr[BUFFSIZE];
  char buf[LARGEBUFFSIZE];
  int  indx=0;
  char methName[16], uriAddr[256], httpVer[64], path[256];
  FILE *fp;
  int  n=0;
  
  while(n<1000){
    recv(clntSock, recvStr, BUFFSIZE, 0);
    snprintf(buf+indx, LARGEBUFFSIZE-indx, "%s", recvStr);
    indx+=strlen(recvStr);
    sscanf(buf, "%s %s %s", methName, uriAddr, httpVer);
    if( strlen(methName)!=0 && strlen(uriAddr)!=0 && strlen(httpVer)!=0){
      break;
    }
    n++;
  }

  if( strcmp(methName, "GET") != 0 ){
    SendErrMsg2Clnt(clntSock, "501 Not Implemented\n");
    return 1;
  }

  fprintf(stdout, "http request: '%s %s %s' by %s:%u\n", methName, uriAddr, httpVer, inet_ntoa(clntAddr.sin_addr), clntAddr.sin_port);

  if( strchr(uriAddr, (int)'?') != NULL ){
    strcpy(path, strtok(uriAddr, "?"));
    strcpy(urlPara, strtok(NULL, "?"));
    //    para = urlPara;
  }
  else{
    strcpy(path, uriAddr);
    strcpy(urlPara, "");
  }  
  if( (fp=fopen(path+1,"r")) == NULL ){
    SendErrMsg2Clnt(clntSock, "404 Not Found\n");        
  }
  
  snprintf(buf, LARGEBUFFSIZE, "%s 200 OK!\r\n", httpVer); send(clntSock, buf, strlen(buf), 0);
  snprintf(buf, LARGEBUFFSIZE, "text/html\r\n");           send(clntSock, buf, strlen(buf), 0);
  snprintf(buf, LARGEBUFFSIZE, "\r\n");                    send(clntSock, buf, strlen(buf), 0);  

  while( fgets(buf, LARGEBUFFSIZE, fp) != NULL ){
    send(clntSock, buf, strlen(buf), 0);
  } 
  fclose(fp);

  return 0;
}

int SendErrMsg2Clnt(int clntSock, char* msg){
    fprintf(stderr, "%s", msg);
    return send(clntSock, msg, strlen(msg), 0);      
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
    gpioWrite(LEDs[m], r);
    m--;
  }  

  return;
}
