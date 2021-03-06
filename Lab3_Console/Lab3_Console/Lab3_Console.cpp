#include "pch.h"
#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"


int main()
{

	HANDLE consoleOutput;
	COORD cursorPos;

	// Получаем хэндл консоли 
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(consoleOutput, &csbi);

	// Задаем координаты курсора и перемещаем курсор
	cursorPos.X = 30;
	cursorPos.Y = 3;
	SetConsoleCursorPosition(consoleOutput, cursorPos);

	// Выводим строку
	printf("Test string at position (30, 3)");

	// Повторяем с другими координатами...
	cursorPos.X = 15;
	cursorPos.Y = 8;
	SetConsoleCursorPosition(consoleOutput, cursorPos);

	printf("Test string at position (15, 8)");

	getchar();

	return 0;
}
