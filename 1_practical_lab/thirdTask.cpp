#include <iostream>


using namespace std;


int main() {
    cout << "Third task is running..." << endl;

    int firstNumber = 1131;
    short firstResult = firstNumber % 10 + int((firstNumber % 100) / 10);

    cout << "First result is: " << firstResult << endl;

    int secondNumber = 9421;
    short secondResult = (int(secondNumber / 100) % 10) * (int(secondNumber / 1000) % 10);

    cout << "Second result is: " << secondResult << endl;

    return 0;
}
