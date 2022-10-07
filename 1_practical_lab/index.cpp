#include <iostream> 
#include <cmath>


using namespace std;


double getFirstTaskFistAnswer(float x, float y, float z, float k) {
    float numerator = sin(pow(x, 2)) + pow(tan(y / (z + 1)), 1/3);
    float divider = pow(exp(k - y) + 2.34*pow((x - 3), 2), 2);
    float term = sqrt(abs(x - y));
    return numerator / divider + term;
}


double getFistTaskSecondAnswer(float x, float y, float z, float k) {
    float numerator = x - z;
    float divider = x + z;

    float term = 3;
    /* cout<<"Debug: "<< numerator << endl; */
    /* cout<<"Debug: "<< atan(abs(numerator / divider)) << endl; */
    return pow(atan(abs(numerator / divider)), 2) + term;
}


float defaultFirstRectCoordinate[2] = {1, 1};
float defaultSecondRectCoordinate[2] = {5, 3};


bool getSecondTaskAnswer(float point[2], float firstRectCoordinate[]=defaultFirstRectCoordinate, float secondRectCoordinate[] = defaultSecondRectCoordinate) {
    try {
        /* if (sizeof(point) != 2) { */
        /*     throw 1; */
        /* } */
        /* cout<<"Debug: first rect coordinate: "<< firstRectCoordinate[0] << " " << firstRectCoordinate[1] << endl; */
        /* cout<<"Debug: point: "<< point[0] << " " << point[1] << endl; */
        /* cout<<"Debug: second rect coordinate: "<< secondRectCoordinate[0] << " " << secondRectCoordinate[1] << endl; */

        if (firstRectCoordinate[0] <= point[0] && point[0] <= secondRectCoordinate[0] && firstRectCoordinate[1] <= point[1] && point[1] <= secondRectCoordinate[1]) {
            return true;
        } 
    } catch(int errCode) {
        switch (errCode) {
            case 1: 
                cout<<"Point coordinates are incorrect please make sure you are using [float, float] array";
                break;
        }
    }
    return false;
}


double getThirdTaskFirstAnswer(int firstNumber) {
    try {
        if (firstNumber < 10) {
            throw 1;
        } 
        return firstNumber % 10 + int((firstNumber % 100) / 10);
    } catch (int errCode) {
        switch (errCode) {
            case 1:
                cout<<"Number should always have at least 2 digits"<<endl;
        }
    }
    return NAN;
}


double getThirdTaskSecondAnswer(int secondNumber) {
    try {
        if (secondNumber < 10) {
            throw 1;
        } 
        /* cout<<"Debug mult: " << secondNumber << "; " << secondNumber << endl; */
        if (!(secondNumber % 100 == secondNumber)) {
            return getThirdTaskSecondAnswer(int(secondNumber / 10));
        }
        return secondNumber % 10 * int((secondNumber % 100) / 10);
    } catch (int errCode) {
        switch (errCode) {
            case 1:
                cout<<"Number should always have at least 2 digits"<<endl;
        }
    }
    return NAN;
}


void printFirstAnswer(float x, float y, float z, float k) {
    float a = getFirstTaskFistAnswer(x, y, z, k);
    float b = getFistTaskSecondAnswer(x, y, z, k);
    cout << a << " and " << b << endl; 
}


void printSecondAnswer(float point[2]) {
    bool res = getSecondTaskAnswer(point);
    cout << res << endl;
}


void printThirdAnswer(int number) {
    float res1 = getThirdTaskFirstAnswer(number);
    float res2 = getThirdTaskSecondAnswer(number);
    cout << "Last(sum): " << res1 << "; First(mult): " << res2 << endl;
}


int main() {
    float k = 3;

    float x = 18;
    float y = 5;
    float z = 8;

    float point[2] = {1, 1}; // tests passed

    printFirstAnswer(x, y, z, k); // photomath is down
    printSecondAnswer(point); // tests passed
    printThirdAnswer(2622);

    return 0;
}

