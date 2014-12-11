#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void tcpserver_init(void);
void tcpserver_run(void);
void tcp_writebuf(char *buf,int len);
void tcp_flush(void);	 
	 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
