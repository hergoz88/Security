#include <winsock.h>
#include "network1.h"

using namespace std;

// InitWSA() - Mengaktifkan Winsock DLL
bool InitWSA(WSADATA *wsa)
{
    // Mengaktifkan Winsock DLL
    int nError = WSAStartup(0x0202, wsa);
    
    // Terjadi error! WSAStartup() return non-zero
    if(nError)
        return false;
    
    if((*wsa).wVersion != 0x0202)
    {
        // Versi socket tidak sesuai
        WSACleanup();
        return false;
    }
    
    return true;
}

// HostToByte() - Mengubah domain name (contoh. google.com)
//                menjadi Byte Order
u_long HostToByte(char *HostName)
{
    LPHOSTENT lpRemoteHost; 
    int i;
    u_long uResult;
    
    lpRemoteHost = gethostbyname(HostName);
    
    i = 0;
    // Jika tipe address adalah AF_INET
    if ((*lpRemoteHost).h_addrtype == AF_INET)
    {
        // Looping untuk mendapatkan byte order dari address
        while((*lpRemoteHost).h_addr_list[i])
             uResult = *(u_long*) (*lpRemoteHost).h_addr_list[i++];
    }
    
    return uResult;
}

// Connect_Addr() - Melakukan koneksi berdasarkan informasi
//                  dari struktur SOCKADDR_IN
SOCKET Connect_Addr(SOCKADDR_IN *addr)
{
    SOCKET sConn, sock;
    
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    // Jika socket gagal dibuat
    if(sock == INVALID_SOCKET || sock == 0)
        return 0; // Akhiri fungsi
        
    sConn = connect(sock, (SOCKADDR*) addr, sizeof(*addr));
    
    if (sConn == INVALID_SOCKET)
        return 0;
        
    return sock;
}

