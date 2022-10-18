#include <iostream>
#include <math.h>

using namespace std;

const float accuracy = 0.012;

int main() {
    float sum = 0;

    int n = 1;
    float current  = ((2 * n) / pow(2 + n, 2)) * ((1) / pow((n + 1), 2));
    float prev = 0;
    do {
        n++;
        prev = current;
        current  = ((2 * n) / pow(2 + n, 2)) * ((1) / pow((n + 1), 2));
        sum += prev;
    } while(abs(current - prev) > accuracy);
    cout << sum;
    return 0;
}
