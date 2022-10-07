#include <iostream>

using namespace std;

int main() {
    float a; cout << "Please input a: "; cin >> a;
    float res;

    if (a < -2) {
        res = 4;
    } else if (a > -1) {
        res = 1;
    } else {
        res = a * a;
    }
    cout << "Result: " << res << endl;
    return 0;
}
