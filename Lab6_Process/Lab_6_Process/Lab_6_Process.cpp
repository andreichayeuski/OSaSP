// Lab_6_Process.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <tlhelp32.h>т
#include "string.h"
#include <iostream>

using namespace std;

TCHAR buf[] = TEXT("chrome.exe");

void search()
{
	WIN32_FIND_DATA FindFileData; // Эта структура описывает файл, найденный функцией FindFirstFile или FindNextFile
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR directorySearch[] = TEXT("C:\\Program Files (x86)\\Internet Explorer");
	TCHAR filesearch[] = TEXT("C:\\Program Files (x86)\\Internet Explorer\\iexplo*.exe");
	// Find the first file in directory
	hFind = FindFirstFile(filesearch, &FindFileData); // поиск в каталоге файла или подкаталога, имя которого соответствует указанному имени файла
	if(hFind == INVALID_HANDLE_VALUE)
	{
		printf("Invalid file handle. Error is %u. \n", GetLastError());
	}
	else
	{
		std::wcout << "Founded process: " << FindFileData.cFileName << '\n';
		// List all the other files in diretory
		while (FindNextFile(hFind, &FindFileData) != 0) // продолжает поиск файлов из предыдущего вызова функции FindFirstFile
		{
			std::wcout << "Found: " << FindFileData.cFileName << '\n';
		}
		FindClose(hFind); // Закрывает дескриптор поиска файлов, открытый функциями FindFirstFile 
	}
	getchar();
	return;
}

void create()
{
	STARTUPINFO cif; // Указывает оконную станцию, рабочий стол, стандартные дескрипторы и внешний вид главного окна процесса во время создания
	ZeroMemory(&cif, sizeof(STARTUPINFO)); // Заполняет блок памяти нулями
	PROCESS_INFORMATION pi; // Содержит информацию о недавно созданном процессе и его основной теме
	TCHAR buf[] = TEXT("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Отчёты\\Lab_6_Process\\Debug\\Lab_6_Process.exe");
	TCHAR process[] = TEXT("Lab_6.exe");
	if (CreateProcess(
		NULL,   // Имя исполняемого модуля
		buf,    // Если исполняемый модуль является 16-разрядным приложением
		NULL,   // Указатель на структуру SECURITY_ATTRIBUTES, которая определяет, может ли возвращенный дескриптор новому объекту потока быть унаследован дочерними 
		        // процессами. Если lpThreadAttributes NULL, дескриптор не может быть унаследован
		NULL,   // Указатель на структуру SECURITY_ATTRIBUTES для потока
		FALSE,  // флаги наследования текущего процесса. Если этот параметр имеет значение ИСТИНА, каждый наследуемый дескриптор вызывающего процесса наследуется новым процессом
		0,      // Флаги, которые управляют классом приоритета и созданием процесса
		NULL,   // Если этот параметр равен NULL , новый процесс использует среду вызывающего процесса
		NULL,   // Если этот параметр равен NULL , новый процесс будет иметь тот же текущий диск и каталог, что и вызывающий процесс.
		&cif,   // Указатель на структуру STARTUPINFO или STARTUPINFOEX
		&pi     // Указатель на структуру PROCESS_INFORMATION, которая получает идентификационную информацию о новом процессе
	))
	{
		std::wcout << "Process " << process << " is running!" << endl;
		std::cout << endl;
	}
	else std::wcout << "Error " << '\n';
	getchar();
	return;
}

void findCreate()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	TCHAR buf[] = TEXT("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Отчёты\\Lab_6_Process\\Debug\\Lab_6_Process.exe");
	TCHAR process[] = TEXT("Lab_6.exe");
	hFind = FindFirstFile(buf, &FindFileData);
	std::wcout << "Founded process: " << FindFileData.cFileName << '\n';
	if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0,
		NULL, NULL, &cif, &pi))
		std::wcout << "Running with PID:" << pi.dwProcessId << '\n';
	else std::wcout << "Error " << '\n';

	HANDLE hProcess = GetCurrentProcess(); //Получает псевдо-дескриптор для текущего процесса

	//Get the Process name
	if(NULL != hProcess)
	{
		cout << "Done, closing in 2 seconds" << endl;
		Sleep(2000);
		BOOL result = TerminateProcess(hProcess, 0); // Завершает указанный процесс и все его потоки
		CloseHandle(hProcess);
	}
	else
	{
		std::wcout << "Error while terminating " << '\n';
	}
	getchar();
	return;
}

void processList()
{
	//Возвращает дескриптор указанного стандартного устройства(стандартный ввод, стандартный вывод или стандартная ошибка)Возвращает дескриптор указанного стандартного устройства(стандартный ввод, стандартный вывод или стандартная ошибка)
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_GREEN);
	// Делает снимок указанных процессов, а также кучи, модули и потоки, используемые этими процессами
	HANDLE hSnapshot = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, // Включает все процессы в системе в моментальном снимке
		0                   // текущий процесс
	); 
	if (hSnapshot)
	{
			PROCESSENTRY32 pe32; // Описывает запись из списка процессов, находящихся в системном адресном пространстве при съемке моментального снимка
			pe32.dwSize = sizeof(PROCESSENTRY32); // Размер структуры в байтах
			if (Process32First(hSnapshot, &pe32)) // Получает информацию о первом процессе, обнаруженном в системном снимке
		{
				do
			{
				std::wcout << "Running ProcName: " << pe32.szExeFile << '\n';
			} while (Process32Next(hSnapshot, &pe32)); // Получает информацию о следующем процессе, записанном в системном снимке
		}
		CloseHandle(hSnapshot);
	}
	getchar();
	return;
}

bool AreaEqual(const TCHAR *a, const TCHAR *b)
{
	while(*a == *b)
	{
		if (*a == TEXT('\0'))
			return true;
		a++; b++;
	}
	return false;
}

bool IsProcessRun()
{
	bool RUN;
	TCHAR buf[] = TEXT("chrome.exe");
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hSnapshot, &pe);
	if (AreaEqual(pe.szExeFile, buf))
	{
		RUN = true;
		return RUN;
	}
	else
		RUN = false;
	while(Process32Next(hSnapshot, &pe))
	{
		if (AreaEqual(pe.szExeFile, buf))
		{
			RUN = true;
			return RUN;
		}
		else
			RUN = false;
	}
	return RUN;
}

void check()
{
	if(IsProcessRun())
	{
		cout << "Process "; wcout << buf; cout << " is running " << endl;
	}
	else
	{
		cout << "Process "; wcout << buf; cout << " is not running " << endl;
	}
	cout << endl;
	return;
}

int main()
{
	int n;
	while(1)
	{
		cout << "0 - Exit" << endl;
		cout << "1 - Find process" << endl;
		cout << "2 - Create process" << endl;
		cout << "3 - Find & create process" << endl;
		cout << "4 - List of process" << endl;
		cout << "5 - Is process running?" << endl;
		cout << "\tChoose: \n\n";
		cin >> n;

		switch(n)
		{
		case 0: exit(0); break;
		case 1: search(); break;
		case 2: create(); break;
		case 3: findCreate(); break;
		case 4: processList(); break;
		case 5: check(); break;
		}

	}
}

