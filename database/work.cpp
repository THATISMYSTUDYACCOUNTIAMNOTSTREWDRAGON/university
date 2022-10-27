#include <iostream>

using namespace std;

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

int menuIndex = 0;
MenuItem *menuItems = new MenuItem[20];
void addMenuItem(MenuItem menuItem) {
    menuItems[menuIndex] = menuItem;
    menuIndex += 1;
}

void generateMenu() {
    addMenuItem(createNewMenuItem("/help", "show help"));
    addMenuItem(createNewMenuItem("/new", "add new student"));
    addMenuItem(createNewMenuItem("/all", "show all students"));
    addMenuItem(createNewMenuItem("/load", "load from text file"));
    addMenuItem(createNewMenuItem("/save", "save in file"));
    addMenuItem(createNewMenuItem("/load_binary", "load binary file"));
    addMenuItem(createNewMenuItem("/delete", "delete student"));
    addMenuItem(createNewMenuItem("/edit/:id", "edit student"));
    addMenuItem(createNewMenuItem("/search/mark/4/count/1", "find students with mark"));
}


void userEctionListener() {

}

int main() {
    return 0;
}