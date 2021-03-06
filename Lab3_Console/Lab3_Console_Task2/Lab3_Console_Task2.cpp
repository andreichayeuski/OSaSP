#include "pch.h"
#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"

void PrintLine(int x, int y, const char* line, int color = 0x5E)
{
	HANDLE consoleOutput;
	COORD cursorPos;
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(consoleOutput, &csbi);

	cursorPos.X = x;
	cursorPos.Y = y;

	SetConsoleCursorPosition(consoleOutput, cursorPos);
	SetConsoleTextAttribute(consoleOutput, color);

	std::cout << line << std::endl;

}

int main()
{
	const char* line = "				";
	const char* symbol = " ";

	char names[20][10] = { "NAME", "", "PETROV" };
	char groups[20][10] = { "GROUP", "", "4" };

	int i = 0;

	for (i = 0; i < 3; i += 2)
	{
		for (int j = 1; j < 13; j++)
		{
			PrintLine(20, j + i, symbol);
		}
		
		for (int j = 1; j < 13; j++)
		{
			PrintLine(21, j + i, symbol);
		}

	}

	PrintLine(0, 0 + i, line);

	system("pause");
	return 0;
}