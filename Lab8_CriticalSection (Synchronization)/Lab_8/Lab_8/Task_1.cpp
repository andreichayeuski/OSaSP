// Lab_8.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(void* lpParameter)
{
	int* counterp = new int();
	counterp = (int*)lpParameter;
	int counter = *counterp;

	while (counter<20)
	{
		Sleep(500);
		counter++;
		printf("\n Counter= %d", counter);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 5;

	unsigned int myCounter = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&z, 0, &myThreadID);
	int CurPr = GetPriorityClass(GetCurrentProcess()); // Получает класс приоритета для указанного процесса
	//Это значение вместе со значением приоритета для каждого потока процесса определяет базовый уровень приоритета каждого потока.

	int   iPriority1 = GetThreadPriority(myHandle);// + CurPr; // Возвращает значение приоритета для указанного потока
	printf("\n Priority is: %d", iPriority1);
	SetThreadPriority( // Устанавливает значение приоритета для указанного потока
		myHandle, 
		THREAD_PRIORITY_ABOVE_NORMAL // Приоритет 1 над классом приоритета
	);
	iPriority1 = GetThreadPriority(myHandle);// + CurPr;
	printf("\n After Change Priority is: %d", iPriority1);

	SetThreadPriority(myHandle, THREAD_PRIORITY_HIGHEST); // Приоритет 2 указывает на приоритетный класс.
	iPriority1 = GetThreadPriority(myHandle);// + CurPr;
	printf("\nThe Highest Priority is: %d", iPriority1);

	SetThreadPriority(myHandle, THREAD_PRIORITY_LOWEST); // Приоритет 2 балла ниже класса приоритета.
	iPriority1 = GetThreadPriority(myHandle);// + CurPr;
	printf("\nThe Lowest Priority is: %d", iPriority1);

	Sleep(5000);
	printf("\n end");
	TerminateThread(myHandle, 0);

	getchar();
	return 0;
}


