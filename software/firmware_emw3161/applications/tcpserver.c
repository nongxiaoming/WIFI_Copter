//#include "stdio.h"
#include "dt.h"
#include "stm32f2xx.h"
#include "tcpserver.h"
#include "mxchipWNET.h"


#define MAX_CLIENT_NUM (4)
#define TCP_LISTEN_PORT (8888)

static int fd_listen = -1, fd_client = -1;
static uint8_t *recv_buf,*send_buf, ip_address[16];
static int send_datalen = 0;
  int len;
  int con = -1;
  int clientfd[8];
  fd_set readfds, exceptfds;
  struct timeval_t tv;
  struct sockaddr_t addr;
	int bufferSize;
	
void tcpserver_init(void)
{
	int i = 0;
  for(i=0;i<MAX_CLIENT_NUM;i++) 
    clientfd[i] = -1;
  recv_buf = (uint8_t *)malloc(1*1024);
	send_buf = (uint8_t *)malloc(1*1024);
	
  tv.tv_sec = 0;
  tv.tv_usec = 100;
	
  set_tcp_keepalive(3, 60);
}

void tcpserver_run(void)
{
	int i, j;
	
    mxchipTick();	
		/*Establish a TCP server that accept the tcp clients connections*/
		if (fd_listen==-1) {
      fd_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);			
			  bufferSize = 5*1024;
				setsockopt(fd_listen,0,SO_RDBUFLEN,&bufferSize,4);
				bufferSize = 5*1024;
				setsockopt(fd_listen,0,SO_WRBUFLEN,&bufferSize,4);
      addr.s_port = TCP_LISTEN_PORT;
      bind(fd_listen, &addr, sizeof(addr));
      listen(fd_listen, 0);
     // printf("TCP server established at port: %d \r\n", addr.s_port);
    }
		
		/*Check status on erery sockets */
		FD_ZERO(&readfds);
		FD_SET(fd_listen, &readfds);	
		if(fd_client!=-1)
		  FD_SET(fd_client, &readfds);
		for(i=0;i<MAX_CLIENT_NUM;i++) {
			if (clientfd[i] != -1)
				FD_SET(clientfd[i], &readfds);
		}
		
		select(1, &readfds, NULL, &exceptfds, &tv);
    
    /*Check tcp connection requests */
		if(FD_ISSET(fd_listen, &readfds))
		{
			j = accept(fd_listen, &addr, &len);
			if (j > 0) {
			  inet_ntoa((char*)ip_address, addr.s_ip );
			 // printf("Client %s:%d connected\r\n", ip_address, addr.s_port);
			  for(i=0;i<MAX_CLIENT_NUM;i++) {
				  if (clientfd[i] == -1) {
					  clientfd[i] = j;
					  break;
				  }
			  }
			}
		}
		
   /*Read data from tcp clients and send data back */ 
	 for(i=0;i<MAX_CLIENT_NUM;i++) {
      if (clientfd[i] != -1) {
        if (FD_ISSET(clientfd[i], &readfds)) {
          con = recv(clientfd[i], recv_buf, 1*1024, 0);
          if (con > 0){
						int index =0;
            while(index <(con-4))
              {
							 if((recv_buf[index]==0xaa)&&(recv_buf[index+1]==0xaf)&&(recv_buf[index+2]>0)&&(recv_buf[index+2]<0xf1))
                {
								 if(recv_buf[index+3]<50)
                 {
								  uint8_t cmd_len = recv_buf[index+3];
									 if(cmd_len+index<con)
                    {
										  dt.Data_Receive_Anl( &recv_buf[index],cmd_len+5);
											index+=cmd_len+5;
										}else
                    {
										index++;
										}
								 }else
                 {
								 index+=4;
								 }
								}else
                {
								 index++;
								}
							}
					}
          else {
            close(clientfd[i]);
            clientfd[i] = -1;
          }
        }
        else if (FD_ISSET(clientfd[i], &exceptfds))
          clientfd[i] = -1;
      }
    }
	 send_datalen = 0;
	 
}
void tcp_writebuf(char *buf,int len)
{
	int i;
	if(send_datalen+len<1024)
	{
 	for(i=0;i<len;i++)
		{
		send_buf[send_datalen++] = buf[i];
	  }
	}
}
void tcp_flush(void)
{
		int i;
   /*Read data from tcp clients and send data back */ 
	 for(i=0;i<MAX_CLIENT_NUM;i++) {
      if (clientfd[i] != -1) {
           if(send_datalen==0)
						 break;
          con = send(clientfd[i], send_buf, send_datalen, 0);
          if (con < 0)  {
            close(clientfd[i]);
            clientfd[i] = -1;
          }
      }
    }
	 mxchipTick();	
	 send_datalen = 0;
}
