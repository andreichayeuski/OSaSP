// LB.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

void outmas(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << "arr[" << i << "] = " << arr[i] << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hHeap;

	int *arr = NULL;
	int h_size = 2048;
	int a_size = 2048;
	int arr_size = 20;

	setlocale(LC_ALL, ".1251");
	//создаем кучу
	hHeap = HeapCreate(HEAP_NO_SERIALIZE, h_size, h_size);
	//распределяем память кучи под массив
	arr = (int*)HeapAlloc(hHeap, NULL, a_size);

	for (int i = 0; i < arr_size; i++)
		arr[i] = i;
	int x = -1;
	while (x != 0) {
		cout << endl;
		cout << "0 - Exit" << endl;
		cout << "1 - Write array" << endl;
		cout << "2 - Add to end" << endl;
		cout << "3 - Delete last element" << endl;
		cout << "4 - Enter element in select position" << endl;
		cout << "5 - Delete element from position" << endl;
		cin >> x;
		system("cls");
		int pos;
		switch (x)
		{
		case 1: {
			outmas(arr, arr_size); 
			break;
		}
		case 2: {
			arr_size++;
			HeapReAlloc(hHeap, *arr, NULL, arr_size * sizeof(int));
			cout << "Enter element " << endl;
			cin >> x;
			arr[arr_size - 1] = x;
			x = -1;
			outmas(arr, arr_size);
			break;
		}
		case 3: {
			arr_size--;
			HeapReAlloc(hHeap, *arr, NULL, arr_size * sizeof(int));
			outmas(arr, arr_size);
			break;
		}
		case 4: {
			pos = -1;
			cout << "Enter position ";
			cin >> pos;
			cout << endl;
			arr_size++;
			HeapReAlloc(hHeap, *arr, NULL, arr_size * sizeof(int));
			for (int i = arr_size; i > pos - 1; i--)
				arr[i] = arr[i - 1];
			cout << endl << "Enter element " << endl;
			cin >> x;
			arr[pos - 1] = x;
			cout << "Size array = " << arr_size;
			outmas(arr, arr_size);
			break;
		}
		case 5: {
			pos = -1;
			cout << "Enter position ";
			cin >> pos;
			cout << endl;
			for (int i = pos - 1; i < arr_size - 1; i++)
				arr[i] = arr[i + 1];
			arr_size -= 1;
			HeapReAlloc(hHeap, *arr, NULL, arr_size * sizeof(int));
			outmas(arr, arr_size);
			break;
		}
		}
	}
}