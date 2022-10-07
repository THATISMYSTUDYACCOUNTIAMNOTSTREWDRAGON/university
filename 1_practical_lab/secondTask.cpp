#include <iostream> 
#include <cmath>
#include <iomanip>


using namespace std;


int main() {
    cout << "Second task runnning" << endl;
    float firstRectCoordinateX = 1;
    float firstRectCoordinateY = 1;

    float secondRectCoordinateY = 3;
    float secondRectCoordinateX = 5;

    float pointX = 1;
    float pointY = 1;

    bool isCollideRect = firstRectCoordinateX <= pointX && pointX <= secondRectCoordinateX && firstRectCoordinateY <= pointY && pointY <= secondRectCoordinateY;

    cout << std::boolalpha;   
    cout << isCollideRect << endl;

    return 0;
}
