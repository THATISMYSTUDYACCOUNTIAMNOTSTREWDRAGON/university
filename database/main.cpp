#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
using namespace std;

char keypress() {
  system ("/bin/stty raw");
  char c;
  system("/bin/stty -echo");
  c = getc(stdin);
  system("/bin/stty echo");
  system ("/bin/stty cooked");
  return c;
}

void editfile(string filename) {
  std::cout << "\033[2J\033[1;1H";
  ofstream file(filename);
  string text = "";
  bool saved = true;
  string save;
  do {
    std::cout << "\033[2J\033[1;1H"; //clear

    if (saved) {
      save = "  |  File is saved";
    } else {
      save = "  |  File has unsaved changes";
    }
    std::cout << filename << "  |  Press ~ to save file and ` to exit" << save << "\n____________________________________________________________________________\n" << text; //display text and header

    system("/bin/stty -raw");
    system("/bin/stty raw"); //change input
    char key = keypress(); //take input
    if (key == 127) { //backspace
      text = text.substr(0, text.length() - 1);
      saved = false;
    } else if (key == 126) { //~ to save
      ofstream file(filename);
      file << text;
      file.close();
      saved = true;
    } else if (key == 13) {
      text += "\n"; //for newlines
      saved = false;
    } else if (key == 96) {
      std::cout << "\033[2J\033[1;1H";
      break;
    } else { //add char
      text += key;
      saved = false;
    }
  } while (true);
}

void readfile(string filename) {
  std::cout << "\033[2J\033[1;1H"; //clear
  ifstream file(filename); //open file to read
  string text;
  std::cout << filename << "  |  Read only mode  |  Press enter to exit \n___________________________________________________\n"; //header
  while (getline (file, text)) {
    cout << text << "\n"; //display
  }
  std::cin.ignore();
  std::cin.ignore(); //wait for keypress
  std::cout << "\033[2J\033[1;1H"; // clear
}

int main() {
  string choic; 
  while (true) {
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Input r to read, e to edit, or c to create. : ";
    char choice = getchar();
    if (choice == 114) {
      std::cout << "Enter the file name, don't forget the file extension : ";
      std::cin >> choic;
      readfile(choic);
    } else if (choice == 101 or 99) {
      std::cout << "Enter the file name, don't forget the file extension : ";
      std::cin >> choic;
      editfile(choic);
    }
  }
}