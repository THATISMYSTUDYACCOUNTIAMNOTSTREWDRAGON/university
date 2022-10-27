#include <iostream>
#include <iomanip>
using namespace std;

void clear() {
    system("clear");
}

void pause() {
	int less;
	cout << "Введите любое число, чтобы продолжить: ";
	cin >> less;
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
MenuItem *menuItems = new MenuItem[menuItemsAmount];

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
    // пределать с callback (сразу блин не дошло как делать)
    addMenuItem(createNewMenuItem("It is not a joke", "use CTRL-c to quit")); // 0
    addMenuItem(createNewMenuItem("/help", "show help")); // 1
    addMenuItem(createNewMenuItem("/new", "add new student")); // 2
    addMenuItem(createNewMenuItem("/all", "show all students")); // 3
    addMenuItem(createNewMenuItem("/search/:mark/?/4/count/?/1", "find students with mark")); // 4
    addMenuItem(createNewMenuItem("/load", "load from text file"));
    addMenuItem(createNewMenuItem("/save", "save in file"));
    addMenuItem(createNewMenuItem("/load_binary", "load binary file"));
    addMenuItem(createNewMenuItem("/delete", "delete student"));
    addMenuItem(createNewMenuItem("/edit/:id", "edit student")); // 4
}

void printMenu() {
    for (int i = 0; i < menuItemsAmount; i++) {
        cout << menuItems[i].id << " " << menuItems[i].name << " " << menuItems[i].description << endl;
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
    FullName fullname; 
    
    char birth[100];
    char group[100];

    int enteranceDate;
    int course;

    Marks marks;
};

Student createStudent() {
    Student student;

    // костыли!!!! переделать!
    cout << "Input name(string): "; cin >> student.fullname.name;
    cout << "Input sername(string): "; cin >> student.fullname.sername;
    cout << "Input patronical(string): "; cin >> student.fullname.patronical;

    cout << "Input birth date(string): "; cin >> student.birth;
    cout << "Input course(int): "; cin >> student.course;
    cout << "Input enterance date(string): "; cin >> student.enteranceDate;
    cout << "Input group(string): "; cin >> student.group;

    cout << "Input sub name1(int): "; cin >> student.marks.name1;
    cout << "Input sub mark1(int): "; cin >> student.marks.mark1;

    cout << "Input sub name2(int): "; cin >> student.marks.name2;
    cout << "Input sub mark2(int): "; cin >> student.marks.mark2;

    cout << "Input sub name3(int): "; cin >> student.marks.name3;
    cout << "Input sub mark3(int): "; cin >> student.marks.mark3;

    return student;
}

int studentsAmount = 0;
Student *storage = new Student[studentsAmount];

void printOneRow() {

}

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


void drawDivider(int width) {
    int magicNumber = 11;
    for (int i = 0; i < width * magicNumber + magicNumber * 2 + 12; i++) {
        cout << "-";
    }
    cout << "\n";
}

void drawHeader(int width) {
	drawDivider(width);
	cout <<
	    " | " << setw(width) << "Sername" <<
		" | " << setw(width) << "Name" <<
		" | " << setw(width) << "Patronical" <<
		" | " << setw(width) << "Enterance Date" <<
		" | " << setw(width) << "Course";
	for (int i = 0; i < 3; i++) {
		cout << " | " << setw(width) << "Subject"
			<< " | " << setw(width) << "Mark";
		if (i == 2) cout << "|" << endl;
	}
	drawDivider(width);
}

void drawRow(Student student, int width) {
	cout << " | " << setw(width) << student.fullname.sername      <<
		    " | " << setw(width) << student.fullname.name         <<
		    " | " << setw(width) << student.fullname.patronical   <<
		    " | " << setw(width) << student.enteranceDate         <<
		    " | " << setw(width) << student.course <<
	        " | " << setw(width) << student.marks.name1     <<
	        " | " << setw(width) << student.marks.mark1     <<
	        " | " << setw(width) << student.marks.name2     <<
	        " | " << setw(width) << student.marks.mark2     <<
	        " | " << setw(width) << student.marks.name3     <<
		    " | " << setw(width) << student.marks.mark3 << "|" << endl;
}

void drawTable() {
    cout << "Drawing is starting..." << endl;
	drawHeader(14);
	for (int i = 0; i < studentsAmount; i++) {
		drawRow(storage[i], 14);
		drawDivider(14);
	}
	char stumb; cout << "Got it? (y): "; cin >> stumb; 
}

// тк мне лень возвращять новый массив выводим в real time
void printSortedStudents() {
    cout << "Drawing is starting..." << endl;
	drawHeader(14);
    for (int i = 0; i < studentsAmount; i++) {
        int sutisfyingResults = 0;
        Student student = storage[i];
        int marks[] = {student.marks.mark3, student.marks.mark2, student.marks.mark1};
        for (int i = 0; i < sizeof(marks) / sizeof(marks[0]); i++) {
            if (marks[i] == 4) {
                sutisfyingResults += 1;
            }
        }
        if (sutisfyingResults == 1) {
		    drawRow(storage[i], 14);
		    drawDivider(14);
        }
    }
	char stumb; cout << "Got it? (y): "; cin >> stumb; 
}

int main() {

    generateMenu();

	setlocale(0, "");

	cout << "(((Press CTRL-c to close program or enter any number to continue))) ;): ";

	int command;
	cin >> command;
	clear();

	while (true) {

        clear();

        printMenu();

		cout << "Enter commands in 0 to 4 range: "; cin >> command;

		if (command == 0) break;


		switch (command) {
		    case 1:
		        printMenu();
			    break;

		    case 2:
                appendStudent();
			    break;

		    case 3:
		        drawTable();
			    break;

		    case 4:
                printSortedStudents();
			    break;

		    case 5:
			    break;

		    case 6:
			    break;

		    case 7:
			    break;

		    case 8:
			    break;

		    case 9:
			    break;

		    case 10:
			    break;

		    default:
			    cout << "Введено некорректное число.\n";
			    char isGotIt;
			    cout << "Wrong input got it (y?) "; cin >> isGotIt;
		}
	}

	return 0;
}
