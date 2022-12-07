#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

enum Fuild {
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

inline const char *getFuildName(Fuild v) {
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

struct KeyValue {
  Fuild key;
  char value[100];
};

struct Student {
  int storageSize;
  KeyValue *storage;
};

struct Storage {
  int storageSize;
  Student *storage;
};

void expandStudentStorage(Student &student) {
  cout << "Expanding student storage" << endl;
  int newStorageSize = student.storageSize + 1;

  KeyValue *newStorage = new KeyValue[newStorageSize];

  for (int i = 0; i < student.storageSize; i++) {
    newStorage[i] = student.storage[i];
  }

  delete[] student.storage;
  student.storage = newStorage;
  newStorage = NULL;

  student.storageSize = newStorageSize;
}

void appendStudentFuild(Student &student, KeyValue keyvalue) {
  cout << "Appending student fuild..." << endl;
  expandStudentStorage(student);
  student.storage[student.storageSize - 1] = keyvalue;
}

Student createNewStudent() {
  cout << "Creating new student..." << endl;
  Student student;

  student.storageSize = 0;
  student.storage = new KeyValue[0];

  for (int i = Fuild::Name; i <= Fuild::Mark3; ++i) {
    KeyValue keyvalue;

    keyvalue.key = (Fuild)i;
    cout << "Input " << getFuildName((Fuild)i) << ": "; cin >> keyvalue.value;
    appendStudentFuild(student, keyvalue);
  }

  return student;
}

void expandGlobalStorage(Storage &storage) {
  cout << "Expanding global storage..." << endl;
  int newStorageSize = storage.storageSize + 1;

  Student *newStorage = new Student[newStorageSize];

  for (int i = 0; i < storage.storageSize; i++) {
    newStorage[i] = storage.storage[i];
  }

  delete[] storage.storage;
  storage.storage = newStorage;
  newStorage = NULL;

  storage.storageSize = newStorageSize;
}

void appendStudent(Storage &storage, Student student) {
  cout << "Appending new student..." << endl;
  expandGlobalStorage(storage);
  storage.storage[student.storageSize - 1] = student;
}

Storage createNewStorage() {
  Storage storage;

  storage.storageSize = 0;
  storage.storage = new Student[0];

  return storage;
}

int main() {

  Storage storage = createNewStorage();

  for (int i = 0; i < 2; i++) {
    Student student = createNewStudent();
    appendStudent(storage, student);
    cout << "=================" << endl;
  }

  for (int i = 0; i < 2; i++) {
    cout << storage.storage[i].storage[0].key << endl;
    cout << storage.storage[i].storage[0].value << endl;
  }

  return 0; 
}
