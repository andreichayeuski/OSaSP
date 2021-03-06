// Lab_7_Threads.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(LPVOID lpParameter)
{
	unsigned int counter = 0;
	while (counter < 20)
	{
		Sleep(1000);
		counter++;
		printf("\n Counter = %d", counter);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(  // Создает поток для выполнения в виртуальном адресном пространстве вызывающего процесса
		0,           // Если lpThreadAttributes NULL, дескриптор не может быть унаследован
		0,           // Исходный размер стека в байтах умолчанию(1 мегабайт)
		myThread,    // Указатель на определенную приложением функцию, которую должен выполнить поток. Этот указатель представляет собой начальный адрес потока
		&myCounter,  // Указатель на переменную, которая должна быть передана потоку
		0,           // Поток запускается сразу после создания
		&myThreadID  // Указатель на переменную, которая получает идентификатор потока
	);
	Sleep(5000);
	printf("\n Main Process ....");
	TerminateThread(myHandle, 0); // Завершает поток
	getchar();
    return 0;
}

