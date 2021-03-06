#include "pch.h"
#include "windows.h"
#include <iostream>
#include <tlhelp32.h>
#include "string.h"

typedef BOOL(WINAPI *SETCONSOLEFONT)(HANDLE, DWORD);     // прототип недокументированый функции
SETCONSOLEFONT SetConsoleFont;

int main()
{

	HANDLE myConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //получить //заголовок потока вывода 
	DWORD cCharsWritten;
	TCHAR str[] = TEXT("HELLO TO EVERYBODY\n");

	HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");   //получить заголовок //программы (модуля) 
	SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
	if (!SetConsoleFont) { std::cout << "error\n"; exit(1); }   //   если ошибка
	SetConsoleFont(myConsoleHandle, 3);  // устанавливаем 3 шрифт.

	SetConsoleTextAttribute(myConsoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	int x = 5; int y = 6;
	COORD pos = { x, y };
	HANDLE hConsole_c = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole_c);

	DWORD len = 18;
	DWORD dwBytesWritten = 0;

	WriteConsoleOutputCharacter(hConsole_c, str, len, pos, &dwBytesWritten);

	pos.X = 10;
	pos.Y = 8;
	SetConsoleCursorPosition(myConsoleHandle, pos);

	WriteConsoleOutputCharacter(hConsole_c, str, len, pos, &dwBytesWritten);

	pos.X = 15;
	pos.Y = 10;
	SetConsoleCursorPosition(myConsoleHandle, pos);

	WriteConsoleOutputCharacter(hConsole_c, str, len, pos, &dwBytesWritten);

	getchar();
	CloseHandle(hConsole_c);

	printf("My name is Andrei");

	return 0;
}
