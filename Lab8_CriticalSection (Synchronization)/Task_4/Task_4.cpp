// Task_4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

DWORD WINAPI myThread(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;

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
		WriteFile(hOut, b, 256, &dwBytes, NULL);
		printf("Thread Written");
		CloseHandle(hOut);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	int z = 0;

	DWORD myThreadID;
	TCHAR Buff[256] = TEXT("HELLO! Students qwerty");
	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)Buff, CREATE_SUSPENDED, &myThreadID);
	BOOL b = SetThreadPriorityBoost(myHandle, false);

	if (b)
	{
		SetThreadPriority(myHandle, THREAD_PRIORITY_HIGHEST);
	}
	ResumeThread(myHandle);

	WaitForSingleObject(myHandle, 10000); // Ожидает, пока указанный объект не окажется в сигнальном состоянии или не истечет интервал тайм-аута.

	printf("\n end");

	TerminateThread(myHandle, 0);

	getchar();

	return 0;
}

