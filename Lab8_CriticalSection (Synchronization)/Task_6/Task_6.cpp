// Task_6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"

CRITICAL_SECTION cs;

DWORD WINAPI myThread(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;
	HANDLE hOut;
	DWORD dwBytes;
	FILE *fp;
	TCHAR stdPath[70] = TEXT("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Lab_8\\myfile.txt");


	EnterCriticalSection(&cs);

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
		printf("Thread  1 Written");
		CloseHandle(hOut);
	}
	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI myThread2(void* lpPar)
{
	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;
	HANDLE hOut;
	DWORD dwBytes;
	FILE *fp;
	TCHAR stdPath[70] = TEXT("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Lab_8\\myfile.txt");

	EnterCriticalSection(&cs);

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
		printf("Thread  2 Written");
		CloseHandle(hOut);
	}
	LeaveCriticalSection(&cs);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int z = 0;

	DWORD myThreadID;
	DWORD myThreadID2;
	TCHAR Buff[256] = TEXT("HELLO! Students qwerty");
	TCHAR Buff2[256] = TEXT("start");

	InitializeCriticalSection(&cs);

	HANDLE myHandle = CreateThread(0, 0, myThread, (void*)Buff, CREATE_SUSPENDED, &myThreadID);
	BOOL b = SetThreadPriorityBoost(myHandle, false);

	if (b)
	{
		SetThreadPriority(myHandle, THREAD_PRIORITY_HIGHEST);
	}

	HANDLE myHandle2 = CreateThread(0, 0, myThread2, (void*)Buff2, CREATE_SUSPENDED, &myThreadID2);

	ResumeThread(myHandle);
	ResumeThread(myHandle2);
	WaitForSingleObject(myHandle, 10000);
	WaitForSingleObject(myHandle2, 10000);
	printf("\n end");

	TerminateThread(myHandle, 0);
	TerminateThread(myHandle2, 0);

	getchar();
	return 0;
}
