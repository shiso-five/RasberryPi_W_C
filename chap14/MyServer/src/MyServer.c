#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT     54321
#define BUFFSIZE 1024

int main(void){
  int sock, recvMsgLen, count=1;
  unsigned int clntAddrLen;
  char buf[BUFFSIZE];
  struct sockaddr_in servAddr, clntAddr, addr;
  char msg[26] = "Hello from Raspberry Pi  ";

  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  clntAddrLen  = sizeof(clntAddr);

  servAddr.sin_family      = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port        = htons(PORT);

  bind(sock, (struct sockaddr *)&servAddr, sizeof(servAddr));

  while(1){
    recvMsgLen = recvfrom(sock, buf, BUFFSIZE, MSG_WAITALL, (struct sockaddr *)&clntAddr, &clntAddrLen);
    if(buf[0] == 'x'){
      break;
    }
    buf[recvMsgLen] = '\0';

    fprintf(stdout, "IP: %s Port: %u Message: %s\n", inet_ntoa(clntAddr.sin_addr), clntAddr.sin_port, buf);

    sprintf(&msg[24], "%d", count);
    count++;

    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.1.39");
    addr.sin_port        = htons(PORT);    

    if( sendto(sock, msg, strlen(msg), MSG_CONFIRM, (struct sockaddr *)&addr, clntAddrLen) != strlen(msg)){
      fprintf(stderr, "Error: sendto() sent a different number of bytes than expected\n");
    }
  }

  close(sock);
  
  return 0;
}
