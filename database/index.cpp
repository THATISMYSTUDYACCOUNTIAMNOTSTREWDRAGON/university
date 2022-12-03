#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

enum Header {
  ID,
  Sername,
  Name,
  Patronical,
  Enterance_Date,
  Course,
  Subject1,
  Mark1,
  Subject2,
  Mark2,
  Subject3,
  Mark3,
};

inline const char *HeaderString(Header v) {
  switch (v) {
  case ID:
    return "ID";
  case Sername:
    return "Sername";
  case Name:
    return "Name";
  case Patronical:
    return "Patronical";
  case Enterance_Date:
    return "Enterance_Date";
  case Course:
    return "Course";
  case Subject1:
    return "Subject1";
  case Mark1:
    return "Mark1";
  case Subject2:
    return "Subject2";
  case Mark2:
    return "Mark2";
  case Subject3:
    return "Subject3";
  case Mark3:
    return "Mark3";

  default:
    return "[Unknown]";
  }
}

void clear() { system("clear"); }

void validateIntegerInput(int number) {
  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "You have entered wrong input" << endl;
      cin >> number;
    }
    if (!cin.fail())
      break;
  }
}

struct MenuItem {
  int id;
  const char *name;
  function<void()> func;
};

int menuItemId = 0;
MenuItem createNewMenuItem(const char name[100], function<void()> func) {
  MenuItem menuItem;

  menuItem.id = menuItemId;
  menuItem.name = name;
  menuItem.func = func;

  menuItemId += 1;

  return menuItem;
}

void cleanOrNot() {
  char y;
  cout << "Clearn output(Y/n): ";
  cin >> y;
  if (y == 'y') {
    clear();
  }
}

int menuItemsAmount = 0;
MenuItem *menuItems = new MenuItem[menuItemsAmount];

void addMenuItem(MenuItem newItem) {
  int newMenuItemsAmount = menuItemsAmount + 1;

  MenuItem *newMenuItems = new MenuItem[newMenuItemsAmount];

  for (int i = 0; i < menuItemsAmount; i++) {
    newMenuItems[i] = menuItems[i];
  }

  newMenuItems[menuItemsAmount] = newItem;

  delete[] menuItems;
  menuItems = newMenuItems;
  newMenuItems = NULL;
  menuItemsAmount = newMenuItemsAmount;
}

void printMenu() {
  for (int i = 0; i < menuItemsAmount; i++) {
    cout << menuItems[i].id << " "
         << " " << menuItems[i].name << endl;
  }
}

struct FullName {
  char name[100];
  char sername[100];
  char patronical[100];
};

struct Marks {
  char name1[100];
  int mark1;

  char name2[100];
  int mark2;

  char name3[100];
  int mark3;
};

struct Student {
  int id;

  FullName fullname;

  char birth[100];
  char group[100];

  int enteranceDate;
  int course;

  Marks marks;
};

Student createStudent(int id) {
  Student student;

  // костыли!!!! переделать!
  cout << "Input name(string): ";
  cin >> student.fullname.name;
  cout << "Input sername(string): ";
  cin >> student.fullname.sername;
  cout << "Input patronical(string): ";
  cin >> student.fullname.patronical;

  cout << "Input birth date(string): ";
  cin >> student.birth;
  cout << "Input course(int): ";
  cin >> student.course;
  cout << "Input enterance date(string): ";
  cin >> student.enteranceDate;
  cout << "Input group(string): ";
  cin >> student.group;

  cout << "Input sub name1(int): ";
  cin >> student.marks.name1;
  cout << "Input sub mark1(int): ";
  cin >> student.marks.mark1;

  cout << "Input sub name2(int): ";
  cin >> student.marks.name2;
  cout << "Input sub mark2(int): ";
  cin >> student.marks.mark2;

  cout << "Input sub name3(int): ";
  cin >> student.marks.name3;
  cout << "Input sub mark3(int): ";
  cin >> student.marks.mark3;

  student.id = id;

  return student;
}

int studentsAmount = 0;
Student *storage = new Student[studentsAmount];

void appendStudent() {
  int newStudentsAmount = studentsAmount + 1;

  Student *newStorage = new Student[newStudentsAmount];

  for (int i = 0; i < studentsAmount; i++) {
    newStorage[i] = storage[i];
  }

  newStorage[studentsAmount] = createStudent(studentsAmount);

  delete[] storage;
  storage = newStorage;
  newStorage = NULL;
  studentsAmount = newStudentsAmount;

  cleanOrNot();
}

void drawDivider(int width) {
  for (int i = 0; i < width; i++) {
    cout << "-";
  }
  cout << "\n";
}

void drawHeader(int width) {
  drawDivider(width * (Header::Mark3 + 2));
  for (int i = Header::ID; i <= Header::Mark3; i++) {
    cout << setw(width) << HeaderString(static_cast<Header>(i)) << '|';
  }
  cout << "\n";
  drawDivider(width * (Header::Mark3 + 2));
}

void drawRow(Student student, int width) {
  cout << setw(width) << student.id << "|" << setw(width)
       << student.fullname.sername << "|" << setw(width)
       << student.fullname.name << "|" << setw(width)
       << student.fullname.patronical << "|" << setw(width)
       << student.enteranceDate << "|" << setw(width) << student.course << "|"
       << setw(width) << student.marks.name1 << "|" << setw(width)
       << student.marks.mark1 << "|" << setw(width) << student.marks.name2
       << "|" << setw(width) << student.marks.mark2 << "|" << setw(width)
       << student.marks.name3 << "|" << setw(width) << student.marks.mark3
       << "|" << endl;
}

void printAll() {
  cout << "Drawing is starting..." << endl;
  int width = 15;
  drawHeader(width);
  for (int i = 0; i < studentsAmount; i++) {
    drawRow(storage[i], width);
    drawDivider(width * (Header::Mark3 + 2));
  }
  cleanOrNot();
}

// тк мне лень возвращять новый массив выводим в real time
void printByQuery() {
  cout << "Drawing is starting..." << endl;
  drawHeader(15);
  for (int i = 0; i < studentsAmount; i++) {
    int sutisfyingResults = 0;
    Student student = storage[i];
    int marks[] = {student.marks.mark3, student.marks.mark2,
                   student.marks.mark1};
    for (int i = 0; i < sizeof(marks) / sizeof(marks[0]); i++) {
      if (marks[i] == 4) {
        sutisfyingResults += 1;
      }
    }
    if (sutisfyingResults >= 1) {
      drawRow(storage[i], 15);
      drawDivider(15 * (Header::Mark3 + 2));
    }
  }
  cleanOrNot();
}

int getMenuEnumId(char *fuild) {
  for (int i = Header::ID; i <= Header::Mark3; i++) {
    if (strcmp(fuild, HeaderString(static_cast<Header>(i))) == 0) {
      return i;
    }
  }
  return -1;
}

void bubble_sort() {
  if (studentsAmount == 0) {
    cout << "Database is empty!" << endl;
    return;
  }
  char fuild[100];
  cout << "Input fuild name you wanna change" << endl;
  cin >> fuild;

  int enumFuild = getMenuEnumId(fuild);


  if (enumFuild == -1) {
    cout << "Incorrect value!" << endl;
    return;
  }

  Student temp;

  for (int i = 0; i < studentsAmount - 1; i++) {
    for (int j = 0; j < studentsAmount - i - 1; j++) {

      char a;
      char b;

      switch (enumFuild) {
      case Header::ID:
        a = storage[j].id;
        b = storage[j + 1].id;
        break;
      case Header::Name:
        a = storage[j].fullname.name[0];
        b = storage[j + 1].fullname.name[0];
        break;
      case Header::Sername:
        a = storage[j].fullname.sername[0];
        b = storage[j + 1].fullname.name[0];
        break;
      case Header::Patronical:
        a = storage[j].fullname.patronical[0];
        b = storage[j + 1].fullname.patronical[0];
        break;
      case Header::Course:
        a = storage[j].course;
        b = storage[j + 1].course;
        break;
      case Header::Enterance_Date:
        a = storage[j].enteranceDate;
        b = storage[j + 1].enteranceDate;
        break;
      case Header::Subject1:
        a = storage[j].marks.name1[0];
        b = storage[j + 1].marks.name1[0];
        break;
      case Header::Subject2:
        a = storage[j].marks.name2[0];
        b = storage[j + 1].marks.name2[0];
        break;
      case Header::Subject3:
        a = storage[j].marks.name3[0];
        b = storage[j + 1].marks.name3[0];
        break;
      case Header::Mark1:
        a = storage[j].marks.mark1;
        b = storage[j + 1].marks.mark1;
        break;
      case Header::Mark2:
        a = storage[j].marks.mark2;
        b = storage[j + 1].marks.mark2;
        break;
      case Header::Mark3:
        a = storage[j].marks.mark3;
        b = storage[j + 1].marks.mark3;
        break;

      default:
        cout
            << "You havent chosen fuild properly. Or you are just havent chosen"
            << endl;
      }

      if (a > b) {
        temp = storage[j];
        storage[j] = storage[j + 1];
        storage[j + 1] = temp;
      }
    }
  }

  cout << "Succesfully sorted" << endl;
}

void edit() {
  int id;
  cout << "Please input user id: ";
  cin >> id;

  validateIntegerInput(id);

  if (0 <= id && id < studentsAmount) {
    char y;
    cout << "Do you wanna change all?(Y/n): ";
    cin >> y;
    if (y == 'y') {
      storage[id] = createStudent(id);
    } else {
      char fuild[100];
      cout << "Input fuild name you wanna change" << endl;
      cin >> fuild;
      int enumFuild = getMenuEnumId(fuild);

      if (enumFuild != -1)
        cout << "Input new value" << endl;

      switch (enumFuild) {
      case Header::ID:
        break;
      case Header::Name:
        cin >> storage[id].fullname.name;
        break;
      case Header::Sername:
        cin >> storage[id].fullname.sername;
        break;
      case Header::Patronical:
        cin >> storage[id].fullname.patronical;
        break;
      case Header::Course:
        cin >> storage[id].course;
        break;
      case Header::Enterance_Date:
        cin >> storage[id].enteranceDate;
        break;
      case Header::Subject1:
        cin >> storage[id].marks.name1;
        break;
      case Header::Subject2:
        cin >> storage[id].marks.name2;
        break;
      case Header::Subject3:
        cin >> storage[id].marks.name3;
        break;
      case Header::Mark1:
        cin >> storage[id].marks.mark1;
        break;
      case Header::Mark2:
        cin >> storage[id].marks.mark2;
        break;
      case Header::Mark3:
        cin >> storage[id].marks.mark3;
        break;

      default:
        cout
            << "You havent chosen fuild properly. Or you are just havent chosen"
            << endl;
      }
    }
  }

  cleanOrNot();
}

void deleteOne() {
  cout << "Startign user deleting" << endl;
  int id;
  cout << "Please input user id: ";
  cin >> id;

  int elements_to_move = studentsAmount - id - 1;

  memmove(&storage[id], &storage[id + 1],
          elements_to_move * sizeof(storage[0]));

  studentsAmount -= 1;

  for (int i = 0; i < studentsAmount; i++) {
    storage[0].id = i;
  }
  cleanOrNot();
}

void readUserInput() {
  printMenu();
  cout << "Enter commands in 0 to xz range or press CTRL-c to exit: ";

  int command;
  cin >> command;

  cout << command << endl;

  validateIntegerInput(command);

  for (int i = 0; i < menuItemsAmount; i++) {
    if (i == command) {
      menuItems[i].func();
    }
  }
  readUserInput();
}

void generateMenu() {
  addMenuItem(createNewMenuItem("show all students", printAll));
  addMenuItem(createNewMenuItem("edit student", edit));
  addMenuItem(createNewMenuItem("delete student", deleteOne));
  addMenuItem(createNewMenuItem("add new student", appendStudent));
  addMenuItem(createNewMenuItem("find students by marks", printByQuery));
  addMenuItem(createNewMenuItem("sort students by fuild", bubble_sort));
}

int main() {

  setlocale(0, "");

  generateMenu();

  readUserInput();

  return 0;
}
