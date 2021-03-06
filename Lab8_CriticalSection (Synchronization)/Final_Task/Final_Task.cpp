// Final_Task.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "string.h"
#include <stdlib.h>
#include <fstream>
#pragma warning (disable : 4996)

CRITICAL_SECTION cs;

DWORD WINAPI myThread(void* lpPar)
{
	//char info[256]="Hello student";
	char info[256];

	TCHAR* b = new TCHAR();
	b = (TCHAR*)lpPar;
	//std::wcout << b;

	wcstombs(info, b, wcslen(b) + 1);

	std::cout << "WRITING : " << info << "\n";
	std::ofstream file("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Lab_8\\myfile.txt");

	EnterCriticalSection(&cs);

	file << info;
	file.close();

	LeaveCriticalSection(&cs);
	return 0;
}

DWORD WINAPI myThread2(void* lpPar)
{
	EnterCriticalSection(&cs);

	std::ifstream file("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Lab_8\\myfile.txt");
	char info[256];

	file.getline(info, 256);
	file.close();
	std::cout << "READ : " << info;

	LeaveCriticalSection(&cs);
	return 0;

}

int _tmain(int argc, _TCHAR* argv[])
{
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

