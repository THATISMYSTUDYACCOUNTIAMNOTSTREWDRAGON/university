#include<iostream>// only header required here
using namespace std;

int main()
{
	char *hello = new char[10];
	for (int i = 0; i < 10; i++) {
		hello[i] = 'B';
	}
	cout << hello;
	int fakk;
	cin >> fakk;
}