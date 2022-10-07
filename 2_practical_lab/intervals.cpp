#include <iostream>

using namespace std;

int main() {
	float a, b, c;

	cout << "X="; cin >> a;
	cout << "Y="; cin >> b;
	cout << "Z="; cin >> c;

    a = 2 <= a && a <= 7.2 ? 0: -2 <= a && a <= -0.5 ? a *= 2 : a;
    b = 2 <= b && b <= 7.2 ? 0: -2 <= b && b <= -0.5 ? b *= 2 : b;
    c = 2 <= c && c <= 7.2 ? 0: -2 <= c && c <= -0.5 ? c *= 2 : c;

    cout << "New x is: " << a << endl;
    cout << "New y is: " << b << endl;
    cout << "New z is: " << c << endl;

    return 0;
}

