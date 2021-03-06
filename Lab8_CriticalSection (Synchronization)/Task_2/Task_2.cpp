// Task_2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(void* lpParameter)
{
	TCHAR Buffer[256] = TEXT("HELLO!");
	HANDLE hOut;
	DWORD dwBytes;
	FILE *fp;

	TCHAR stdPath[70] = TEXT("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Lab_8\\myfile.txt");
	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hOut == INVALID_HANDLE_VALUE)
	{
		printf("ERROR WRITING FILE");
		return 2;
	}
	else
	{
		WriteFile(hOut, Buffer, 256, &dwBytes, NULL);
		printf("Thread Written");
		CloseHandle(hOut);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 0;
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)&z, 
		CREATE_SUSPENDED, // Поток создается в приостановленном состоянии и не запускается до тех пор, пока не будет вызвана функция ResumeThread 
		&myThreadID);

	BOOL b = SetThreadPriorityBoost( // Отключает или дает возможность системе временно повысить приоритет потока.
		myHandle, 
		false); //  динамическое повышение включено
	if (b)
	{
		SetThreadPriority(myHandle, THREAD_PRIORITY_HIGHEST);
	}
	ResumeThread(myHandle); // Уменьшает количество приостановленных потоков. 
	// Когда счетчик приостановки уменьшается до нуля, выполнение потока возобновляется.

	Sleep(2000);
	printf("\n end");

	TerminateThread(myHandle, 0); // Завершает поток.
	getchar();

	return 0;
}
