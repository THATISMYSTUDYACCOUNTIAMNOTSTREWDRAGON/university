#include <iostream>

using namespace std;

const int limit = 2;

int main() {
    float mult = 1;

    for (int i = 1, j = 1; i <= limit; i++, j++) {
        mult *= 1.0 / (float)(i + j * j);
        cout << "Item: " << 1.0 / (float)(i + j * j) << endl;
        cout << "Mult: " << mult << endl;
    }

    cout << mult;

    return 0;
}
