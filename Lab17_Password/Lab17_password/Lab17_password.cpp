#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "string.h"
#include "conio.h"

#define STRLEN(x) (sizeof(x)/sizeof(TCHAR)-1)

using namespace std;
ifstream file("D:\\Документы\\Университет\\5 семестр\\ОСиСП\\Отчёты\\OSaSP\\Lab17_password\\output.txt");
HANDLE output;
COORD cursor;
int x = 10;
int y = 3;
const TCHAR szMsg[] = L"Input password:";
char carr[5], password[6];
DWORD dwCount = 0;
int _tmain(int argc, _TCHAR* argv[])
{
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(output, cursor);
	WriteConsole(output, &szMsg, STRLEN(szMsg), &dwCount, NULL);
	cursor.Y++;
	SetConsoleCursorPosition(output, cursor);
	char ch;
	file.getline(password, 6);
	file.close();
	int i = 0;
	bool priz = true;
	for (int i = 0; i < 5; i++)
	{
		ch = getchar();
		if (ch == '\0')
		{
			continue;
		}
		carr[i] = ch;
		switch (i)
		{
		case 0:
			if (!(ch == password[i]))
				priz = false;
			break;

		case 1:
			if (!(ch == password[i]))
				priz = false;
			break;
		case 2:
			if (!(ch == password[i]))
				priz = false;
			break;

		case 3:
			if (!(ch == password[i]))
				priz = false;
			break;

		case 4:
			if (!(ch == password[i]))
				priz = false;
			break;
		}

		ch = '*';

		SetConsoleCursorPosition(output, cursor);
		printf("%c", ch);

		cursor.X++;

	}
	if (priz)
	{
		cursor.Y++;
		SetConsoleCursorPosition(output, cursor);
		cout << "OK!" << std::endl;
	}
	else
	{
		cursor.Y++;
		SetConsoleCursorPosition(output, cursor);
		cout << "GAME OVER!" << std::endl;
	}
	return 0;
}
