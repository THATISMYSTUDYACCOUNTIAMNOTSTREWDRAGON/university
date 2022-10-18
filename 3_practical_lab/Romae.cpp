#include <cmath>
#include <iostream>
using namespace std;
int main() {
    double sum = 0;
    int n = 2;
    double previous;
    double current = 5.0 / 6;
    do {
        previous = current;
        sum += current;
        current = 1 / pow(2, n) + 1 / pow(3, n);
        n++;
        cout << "I: " << n << endl;
        cout << "Sum: " << sum << endl;
        cout << "Item: " << current << endl;
        cout << "Dif: " << fabs(previous - current) << endl;
    } while (fabs(previous - current) > 0.001);
    cout << sum;
    return 0;
}
