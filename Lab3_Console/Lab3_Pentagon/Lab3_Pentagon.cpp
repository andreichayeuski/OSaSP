#include "pch.h"
#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"

int main()
{
	HANDLE consoleOutput;
	COORD cursorPos;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int x = 50, y = 2;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(consoleOutput, &csbi);
	SetConsoleTextAttribute(consoleOutput, 0x3a); // первая цифра - фон, вторая - цвет текста

	for (int i = 0; i < 10; i++)
	{
		cursorPos.X = x - (i * 4);
		cursorPos.Y = y + i;
		SetConsoleCursorPosition(consoleOutput, cursorPos);
		for (int j = 0; j < 8 * i + 1; j++)
		{
			std::cout << " ";
		}
	}
	x = 14;
	y = 11;
	for (int i = 9; i > 0; i--)
	{
		cursorPos.X = x + ((9 - i) * 2);
		cursorPos.Y = y + (9 - i);
		SetConsoleCursorPosition(consoleOutput, cursorPos);
		for (int j = 0; j < 8 * i + (9 - i) * 4 + 1; j++)
		{
			std::cout << " ";
		}
	}

	cursorPos.X = 0;
	cursorPos.Y = 22;
	SetConsoleCursorPosition(consoleOutput, cursorPos);

	system("pause");
	return 0;
}