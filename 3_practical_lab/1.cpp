#include <iostream>
#include <math.h>

using namespace std;

const float accuracy = 0.012;

int main() {
    auto An = [](int n){
        return ((2 * n) / pow(2 + n, 2)) * ((1) / pow((n + 1), 2));
    };

    float sum = 0;

    int i = 1;
    while ( (abs(An(i) - An(i + 1))) > accuracy) {
        sum += An(i);
        i++;
    }
    sum += An(i + 1);

    cout << sum;
    return 0;
}
