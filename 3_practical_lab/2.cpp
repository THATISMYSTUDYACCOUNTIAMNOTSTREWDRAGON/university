#include <iostream>
#include <math.h>


using namespace std;

int main() {
    int n; cout << "N: "; cin >> n;
    float x; cout << "X: "; cin >> x;
    float a; cout << "A: "; cin >> a;

    for (int i = 0; i < n; i++) {
        cout << "WOrk" << endl;
        x = pow((x + a), 2);
    }

    x += a;

    cout << x;
    return 0;
}
