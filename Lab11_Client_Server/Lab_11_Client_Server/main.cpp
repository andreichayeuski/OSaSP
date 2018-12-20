#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <iostream>
 #pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512

using namespace std;

int main(void)
{
	setlocale(LC_ALL, "Russian");
	char recvbuf[DEFAULT_BUFLEN];
	WORD sockVer;
	WSADATA wsaData;  // ��������� WSADATA �������� ���������� � ���������� Windows Sockets.
	int retVal;

	sockVer = MAKEWORD(2, 2);

	WSAStartup(       // ������� WSAStartup ���������� ������������� Winsock DLL ���������.
		sockVer,      // ����� ������� ������ ������������ Windows Sockets, ������� ����� ������������ ����������.
		&wsaData      // ��������� �� ��������� ������ WSADATA, ������� ������ �������� ���������� � ���������� Windows Sockets.
	);

	//������� �����
	SOCKET servSock = socket(   // ������� ������ ������� �����, ����������� � ������������� ���������� ������������ �����.
		PF_INET,                // ��������� ����������
		SOCK_STREAM,            // ��� ������, ������� ������������ ����������������, �������� ������������� ������ ������ �� ������ ����������  
		IPPROTO_TCP             // �������� ���������� ��������� (TC. 
	);

	if (servSock == INVALID_SOCKET)
	{
		printf("Unable to create socket\n");
		getchar();
		WSACleanup();
		return SOCKET_ERROR;
	}
	SOCKADDR_IN sin;
	sin.sin_family = PF_INET;
	sin.sin_port = htons(1111);
	sin.sin_addr.s_addr = INADDR_ANY;

	retVal = bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to bind\n");
		WSACleanup();
		return SOCKET_ERROR;
	}

	//�������� ������ ������� �����
	retVal = listen(servSock, 
		10); // ������������ ����� ������� ��������� ����������.
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to listen\n");
		WSACleanup();
		return SOCKET_ERROR;
	}
	//���� �������
	SOCKET clientSock;

	clientSock = accept(  // ������� accept ��������� ������� ��������� ���������� � ������.
		servSock,         // ����������, ������� �������������� �����, ������� ��� ������� � ��������� ������������� � �������� ������������� 
		NULL,             // �������������� ��������� �� �����, ������� ��������� ����� ��������������� �������, ��� �������� ������ �����. 
		NULL              // �������������� ��������� �� ����� �����, ������� �������� ����� ���������, �� ������� ��������� �������� addr 
	);

	if (clientSock == INVALID_SOCKET)
	{
		printf("Unable to accept\n");
		WSACleanup();
		return SOCKET_ERROR;
	}

	/*char szReq[8];
	retVal = recv(clientSock, szReq, 8, 0);*/
	retVal = recv(         // ������� recv ��������� ������ �� ������������� ������ ��� ���������� ������ ��� ������������ ����������.
		clientSock,        // ����������, ������� �������������� ������������ �����.
		recvbuf,           // ��������� �� ����� ��� ������ �������� ������.
		strlen(recvbuf),   // ����� � ������ ������, �� ������� ��������� �������� buf .
		0                  // ����� ������, �������� �� ��������� ���� �������.
	);

	{          for (;;) {
		if (retVal > 0) {
			cout << "������� " << retVal << " ����" << endl;
			for (int i = 0; i < retVal; i++) {
				cout << recvbuf[i];
			}
			cout << endl << endl;

			if (retVal == SOCKET_ERROR)
			{
				printf("Unable to recv\n");
				return SOCKET_ERROR;
			}

			//printf("Got the request from client\n%s\n", szReq);


			// const char *szResp = "Response";

			printf("Sending response from server\n");
			getchar();
			char userBuff[20] = "";
			std::cout << "Enter text: ";
			std::cin >> userBuff;

			// retVal = send(clientSock, szResp, strlen(szResp), 0);
			retVal = send(clientSock, userBuff, retVal, 0);

			//retVal = send(clientSock, userBuff.c_str(), userBuff.length(), 0);

			if (retVal == SOCKET_ERROR)
			{
				printf("Unable to send\n");
				return SOCKET_ERROR;
			}
		}
	}
		//��������� �����
		closesocket(clientSock);
		closesocket(servSock);

		WSACleanup();
		return 0;
	}
}
