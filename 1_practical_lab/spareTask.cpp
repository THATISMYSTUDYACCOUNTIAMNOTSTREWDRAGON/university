#include<iostream>
#include <iomanip>

using namespace std;

int main() {
  float topY = 4;
  float bottomY = 3;

  float pointX = 1;
  float pointY = 3.1;

  bool isCollide = bottomY <= pointY && pointY <= topY && 
  (pointY - 1) / 2 <= pointX && pointX <= (pointY - 2) / 0.5;

  cout << std::boolalpha;   
  cout << isCollide << endl;

  return 0;
}

