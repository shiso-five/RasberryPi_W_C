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
#define LED0          9
#define LED1          10

int  httpd(int, struct sockaddr_in, char *);
int  SendErrMsg2Clnt(int, char*);
void Configure(void);

int main(void){
  int servSock, clntSock;
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
    if( strstr(urlPara, "LED0=ON") ){      
      //      fprintf(stdout, "URL parameter is '%s'\n", urlPara);
      gpioWrite(LED0, ON);
    }
    else if( strstr(urlPara, "LED0=OFF") ){      
      //      fprintf(stdout, "URL parameter is '%s'\n", urlPara);
      gpioWrite(LED0, OFF);      
    } 
    else if( strstr(urlPara, "LED1=ON") ){      
      //      fprintf(stdout, "URL parameter is '%s'\n", urlPara);
      gpioWrite(LED1, ON);      
    }
    else if( strstr(urlPara, "LED1=OFF") ){      
      //      fprintf(stdout, "URL parameter is '%s'\n", urlPara);
      gpioWrite(LED1, OFF);      
    }    
//    else{
//      fprintf(stdout, "URL parameter is NULL\n");
//    }    

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
  gpioSetMode(LED0, PI_OUTPUT);
  gpioWrite(LED0, OFF);
  gpioSetMode(LED1, PI_OUTPUT);
  gpioWrite(LED1, OFF);  
  
  return;
}
