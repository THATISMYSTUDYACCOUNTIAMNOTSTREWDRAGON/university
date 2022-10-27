#include <iostream>

using namespace std;

struct FullName {
    char name[100];
    char sername[100];
    char patronical[100];
};

struct Marks {
    int mark1;
    int mark2;
    int mark3;
};

struct Student {
    FullName fullname; 
    
    char birth[100];
    char course[100];

    int date;
    char group[100];
};

Student createStudent() {
    Student student;

    cout << "Input name: "; cin >> student.fullname.name;
    cout << "Input sername: "; cin >> student.fullname.sername;
    cout << "Input patronical: "; cin >> student.fullname.patronical;

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

    newStorage[studentsAmount] = createStudent();

    delete []storage;
    storage = newStorage;
    newStorage = NULL;
    studentsAmount = newStudentsAmount;
}

struct MenuItem {
    int id;
    const char *name;
    const char *description;
};

int menuItemId = 0;
MenuItem createNewMenuItem(const char name[100], const char description[100]) {
    MenuItem menuItem;

    menuItem.id = menuItemId;
    menuItem.name = name;
    menuItem.description = description;

    menuItemId += 1;

    return menuItem;
}

int menuItemsAmount = 0;
MenuItem *menuItems = new MenuItem[studentsAmount];

void addMenuItem(MenuItem newItem) {
    int newMenuItemsAmount = menuItemsAmount + 1;

    MenuItem *newMenuItems = new MenuItem[newMenuItemsAmount];

    for (int i = 0; i < menuItemsAmount; i++) {
        newMenuItems[i] = menuItems[i];
    }

    newMenuItems[menuItemsAmount] = newItem;

    delete []menuItems;
    menuItems = newMenuItems;
    newMenuItems = NULL;
    menuItemsAmount = newMenuItemsAmount;
}

void generateMenu() {
    addMenuItem(createNewMenuItem("It is not a joke", "use CTRL-c to quit")); // 0
    addMenuItem(createNewMenuItem("/help", "show help")); // 1
    addMenuItem(createNewMenuItem("/new", "add new student")); // 2
    addMenuItem(createNewMenuItem("/all", "show all students")); // 3
    addMenuItem(createNewMenuItem("/load", "load from text file"));
    addMenuItem(createNewMenuItem("/save", "save in file"));
    addMenuItem(createNewMenuItem("/load_binary", "load binary file"));
    addMenuItem(createNewMenuItem("/delete", "delete student"));
    addMenuItem(createNewMenuItem("/edit/:id", "edit student"));
    addMenuItem(createNewMenuItem("/search/mark/4/count/1", "find students with mark"));
}

void printMenu() {
    for (int i = 0; i < menuItemsAmount; i++) {
        cout << menuItems[i].id << " " << menuItems[i].name << " " << menuItems[i].description << endl;
    }
}

int main() {
    generateMenu();
    printMenu();
     
    return 0;
}


