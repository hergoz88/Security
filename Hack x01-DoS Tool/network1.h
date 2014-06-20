#ifndef _NETWORK1_
#define _NETWORK1_

bool InitWSA(WSADATA*);
u_long HostToByte(char *HostName);
SOCKET Connect_Addr(SOCKADDR_IN *addr);

#endif
