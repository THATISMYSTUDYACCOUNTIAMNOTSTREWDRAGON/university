#include<iostream>// only header required here
#include<stdio.h>
#include<windows.h>
#include <locale>

using namespace std;

int main() {
	
    system("chcp 1251");
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

	cout << "Работай";
	// char arr[200] = {};

	// int i = 0;

	// char character='a';
	// do {
	// 	arr[i] = character;
	// 	character++;
	// 	i++;
	// } while(character<='z');

	// character='A';
	// do {
	// 	arr[i] = character;
	// 	character++;
	// 	i++;
	// } while(character<='Z');

	// character='0';
	// do {
	// 	arr[i] = character;
	// 	character++;
	// 	i++;
	// } while(character<='9');

	// character='а';
	// do {
	// 	arr[i] = character;
	// 	character++;
	// 	i++;
	// } while(character <= 'я');

	// for (int j = 0; j < sizeof(arr) / sizeof(arr[0]); j++) {
	// 	cout << arr[j] << endl;
	// }

	return 0;
}