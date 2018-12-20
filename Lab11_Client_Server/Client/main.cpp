#include <stdio.h>
#include <winsock2.h>
#include <string>
#include <iostream>
  #pragma comment(lib, "Ws2_32.lib")
#pragma warning (disable: 4996)
#define bufsize 256

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;
    int retVal=0;
	char buf[bufsize];
	int r;
 
    WSAStartup(ver,(LPWSADATA)&wsaData);
 
    LPHOSTENT hostEnt;
 
    hostEnt = gethostbyname("localhost");
 
    if(!hostEnt)
    {
        printf("Unable to collect gethostbyname\n");
        WSACleanup();
        return 1;
    }
 
    //Создаем сокет
    SOCKET clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
 
    if(clientSock == SOCKET_ERROR)
    {
        printf("Unable to create socket\n");
        WSACleanup();
        return 1;
    }
 
    SOCKADDR_IN serverInfo;
 
    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
    serverInfo.sin_port = htons(1111);
 
    retVal=connect(clientSock,(LPSOCKADDR)&serverInfo, sizeof(serverInfo));
    if(retVal==SOCKET_ERROR)
    {
        printf("Unable to connect\n");
        WSACleanup();
        return 1;
    }
 
    printf("Connection made sucessfully\n");
 
    //const char *pBuf = "Request";
 
  //  printf("HELLO FROM CKIENT!!!\n");
	std::string userBuff = "";
	std::cout << "Enter text: ";
	std::getline(std::cin, userBuff);
	//retval = WriteFile(hPipe, userBuff.c_str(), userBuff.length(), &dwRead, NULL);

//    retVal = send(clientSock, pBuf, strlen(pBuf), 0);
	retVal = send(clientSock, userBuff.c_str(), userBuff.length(), 0);
 
    if(retVal == SOCKET_ERROR)
    {
        printf("Unable to send\n");
		getchar();
        WSACleanup();
        return 1;
    }
 
 
   /* char szResponse[8];
    retVal = recv(clientSock, szResponse, 9, 0);*/

	do
	{
		r = recv(clientSock, buf, bufsize, 0);
		if (r > 0) {
			cout << "Принято " << r << " байт" << endl;
			for (int i = 0; i < r; i++) {
				cout << buf[i];
			}
			cout << endl << endl;
			break;
		}
		else if (r == 0)
			cout << "Соединение разорвано" << endl;
		else
			cout << "Ошибка в recv(): " << WSAGetLastError() << endl;
	} while (r > 0);
 
    if(retVal == SOCKET_ERROR)
    {
        printf("Unable to recv\n");
        WSACleanup();
        return 1;
    }
 
    //printf("Got the response from server\n%s\n",szResponse);
    getchar();
    closesocket(clientSock);
    WSACleanup();
 
    return 0;
}
