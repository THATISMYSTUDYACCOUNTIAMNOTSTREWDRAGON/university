#include <iostream>
#include <Windows.h>
#include <conio.h> 

using namespace std;

#define CTRL(c) ((c) & 037)

void clear() {	
    COORD cursorPosition;	
    cursorPosition.X = 0;	
    cursorPosition.Y = 0;	
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

char keypress() {
    char c;
    c = getch();
    return c;
}

struct MenuItem {
    int id;
    const char *name;
    const char *description;
};

struct Point {
    int x;
    int y;
};

struct EditorState {
    int currentState;
    int insertState = 0;
    int commandState = 1;
};


struct View {
    Point currentCursorCoordinates;

    EditorState editorState;

    int width;
    int height;

    int messageZoneSize;
    char *messageLineZone;
    Point messageLineCoordinates;

    int commandZoneSize;
	char *commandLineZone;
    Point commandLineCoordinates;

    char *insertZone;
    int insertZoneSize;
    Point insertZoneCoordinates;

    char *markup;
};

void setCursor(Point point) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = point.x;
    coordinates.Y = point.y;
    SetConsoleCursorPosition ( handle , coordinates );
}

Point getCursorPosition(){ 
    Point point;

	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE); 
	if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo)) 
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
	point.x = screenBufferInfo.dwCursorPosition.X; 
	point.y = screenBufferInfo.dwCursorPosition.Y;

    return point;
}

void scrollUp() {
    Point point;
    point.x = 0;
    point.y = 0;
    setCursor(point);
}


void setViewResolution(View &view) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    view.width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    view.height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    view.width = (int)(w.ws_col);
    view.height = (int)(w.ws_row);
#endif
}

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

void printMenu() {
    clear();

    for (int i = 0; i < menuIndex; i++) {
        cout << menuItems[i].id << " " << menuItems[i].name << " " << menuItems[i].description << endl;
    }

    char gotIt;
    cout << "Did you get it? (y/n): "; cin >> gotIt;
}

View viewGenerateBaseMarkup() {
    View view;

    setViewResolution(view);

    view.insertZoneSize = (view.height - 2) * view.width;
    view.messageZoneSize = view.width;
    view.commandZoneSize = view.width;

    view.insertZone = new char[view.insertZoneSize];
    view.messageLineZone = new char[view.messageZoneSize];
    view.commandLineZone = new char[view.commandZoneSize];

    view.insertZoneCoordinates.x = 0;
    view.insertZoneCoordinates.y = 1;

    view.messageLineCoordinates.x = 0;
    view.messageLineCoordinates.y = 0;

    view.commandLineCoordinates.x = 0;
    view.commandLineCoordinates.y = view.height - 1;

    for (int i = 0; i < view.insertZoneSize; i++) {
        view.insertZone[i] = ' ';
    }

    for (int i = 0; i < view.messageZoneSize; i++) {
        view.messageLineZone[i] = ' ';
    }

    for (int i = 0; i < view.commandZoneSize; i++) {
        view.commandLineZone[i] = ' ';
    }

    return view;
}

void cleanMessage(View &view) {
    for (int i = 0; i < view.messageZoneSize; i++) {
        view.messageLineZone[i] = ' ';
    }
}

void printMessage(View &view, char const message[120]) {
    cleanMessage(view);
    for (int i = 0; i < view.messageZoneSize; i++) {
        view.messageLineZone[i] = message[i];
    }
}

const int editorSize = 3600 + 1;

void mergeViewComponenets(View &view) {
    char vm[editorSize] = {};

    for (int i = 0; i < view.messageZoneSize; i++) {
        vm[i] = view.messageLineZone[i];
    }

    for (int i = 0; i < view.insertZoneSize; i++) {
        vm[i + view.messageZoneSize] = view.insertZone[i];
    }

    for (int i = 0; i < view.commandZoneSize; i++) {
        vm[i + view.messageZoneSize + view.insertZoneSize] = view.commandLineZone[i];
    }

    cout << vm;
}

void updateView(View &view) {
    view.currentCursorCoordinates = getCursorPosition();

    hideCursor();
    clear();
    mergeViewComponenets(view);

    setCursor(view.currentCursorCoordinates);

    // scrollUp();
}

void changeMode(View &view) {
    if (view.editorState.currentState == view.editorState.commandState) {
        printMessage(view, "Command mode. Type command ex: /help        ");
        updateView(view);
        setCursor(view.commandLineCoordinates);
    }
    if (view.editorState.currentState == view.editorState.insertState) {
        printMessage(view, "Insert mode. Data will insert into database.");
        updateView(view);
        setCursor(view.insertZoneCoordinates);
    }
}

void commandKeyPressListener(View &view) {
    char key = keypress(); 

    if (key == CTRL(']') && view.editorState.currentState != view.editorState.commandState) {
        view.editorState.currentState = view.editorState.commandState;
        changeMode(view);
        commandKeyPressListener(view);
    }
    if (key == CTRL('[') && view.editorState.currentState != view.editorState.insertState) {
        view.editorState.currentState = view.editorState.insertState;
        changeMode(view);
        commandKeyPressListener(view);
    }

    if (view.editorState.currentState == view.editorState.commandState) {
        // cout << int(key);
        Point cursorCurrent = getCursorPosition();        


        if (int(key) == 8 && cursorCurrent.x >= 0) { // backspace
            cursorCurrent.x -= 1;
        } else {
            cout << cursorCurrent.x;
            view.commandLineZone[2] = key;
            cursorCurrent.x += 1;
        }

        setCursor(cursorCurrent);
        updateView(view);
    }



    commandKeyPressListener(view);
}

int main() {
    // show commands to user
    generateMenu();
    printMenu();

    // generate view
    View view = viewGenerateBaseMarkup();
    updateView(view);

    // set default edit mode
    view.editorState.currentState = view.editorState.commandState;
    changeMode(view);
    
    // listen user actions
    commandKeyPressListener(view);

    // get input
    int fakk;
    cin >> fakk; 
    return 0;    
}