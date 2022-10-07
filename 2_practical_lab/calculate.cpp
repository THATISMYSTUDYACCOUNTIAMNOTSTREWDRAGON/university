#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int M; cout << "Please input integer number: "; cin >> M;
    int n = M % 5;

    float y;

    switch (n) {
        case 1:
            y = (n / sqrt(pow(n, 5))) + abs(pow(n, 8) + 5);
            break;

        case 2:
        case 3:
            y = atan(n + 2);
            break;

        case 4:
            y = sin(n + M_PI / 4);
            break;

        case 0:
        case 5:
            y = exp(n);
            break;
    } 

    cout << "Result: " << y << endl;

    return 0;
}
