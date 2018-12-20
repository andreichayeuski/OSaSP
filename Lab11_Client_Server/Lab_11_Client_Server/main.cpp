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
	WSADATA wsaData;  // Структура WSADATA содержит информацию о реализации Windows Sockets.
	int retVal;

	sockVer = MAKEWORD(2, 2);

	WSAStartup(       // Функция WSAStartup инициирует использование Winsock DLL процессом.
		sockVer,      // Самая высокая версия спецификации Windows Sockets, которую может использовать вызывающий.
		&wsaData      // Указатель на структуру данных WSADATA, которая должна получать информацию о реализации Windows Sockets.
	);

	//Создаем сокет
	SOCKET servSock = socket(   // Функция сокета создает сокет, привязанный к определенному поставщику транспортных услуг.
		PF_INET,                // семейство протоколов
		SOCK_STREAM,            // Тип сокета, который обеспечивает последовательные, надежные двухсторонние потоки байтов на основе соединения  
		IPPROTO_TCP             // Протокол управления передачей (TC. 
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

	//Пытаемся начать слушать сокет
	retVal = listen(servSock, 
		10); // Максимальная длина очереди ожидающих соединений.
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to listen\n");
		WSACleanup();
		return SOCKET_ERROR;
	}
	//Ждем клиента
	SOCKET clientSock;

	clientSock = accept(  // Функция accept допускает попытку входящего соединения в гнездо.
		servSock,         // Дескриптор, который идентифицирует сокет, который был помещен в состояние прослушивания с функцией прослушивания 
		NULL,             // Необязательный указатель на буфер, который принимает адрес соединительного объекта, как известно уровню связи. 
		NULL              // Необязательный указатель на целое число, которое содержит длину структуры, на которую указывает параметр addr 
	);

	if (clientSock == INVALID_SOCKET)
	{
		printf("Unable to accept\n");
		WSACleanup();
		return SOCKET_ERROR;
	}

	/*char szReq[8];
	retVal = recv(clientSock, szReq, 8, 0);*/
	retVal = recv(         // Функция recv принимает данные из подключенного сокета или связанного сокета без установления соединения.
		clientSock,        // Дескриптор, который идентифицирует подключенный сокет.
		recvbuf,           // Указатель на буфер для приема входящих данных.
		strlen(recvbuf),   // Длина в байтах буфера, на который указывает параметр buf .
		0                  // Набор флагов, влияющий на поведение этой функции.
	);

	{          for (;;) {
		if (retVal > 0) {
			cout << "Принято " << retVal << " байт" << endl;
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
		//Закрываем сокет
		closesocket(clientSock);
		closesocket(servSock);

		WSACleanup();
		return 0;
	}
}
