#include <iostream> 
#include <cmath>


using namespace std;


int main() {
    cout << "First task running..." << endl;

    float k = 3;

    float x = 18;
    float y = 5;
    float z = 8;

    float numerator1 = sin(pow(x, 2)) + pow(tan(y / (z + 1)), 1/3);
    float divider1 = pow(exp(k - y) + 2.34*pow((x - 3), 2), 2);
    float term1 = sqrt(abs(x - y));

    cout << "First task first answer: " << numerator1 / divider1 + term1 << endl;

    float numerator2 = x - z;
    float divider2 = x + z;
    float term2 = 3;

    cout << "First task second answer: " << pow(atan(abs(numerator2 / divider2)), 2) + term2 << endl;

    return 0;
}
