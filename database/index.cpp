#include<iostream>
#include<math.h>
#include<cmath>
#include <winuser.h>
#include <functional>
 
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <conio.h> 
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux
 
using namespace std;

const int MAX_STRING_LENGTH = 1000;
const int MAX_MARKUP_SIZE = 400;
const int AMOUNT_NAVIGATION_ITEMS = 10;
char DEFAULT_MENU_ITEM_DESCRIPTION[MAX_STRING_LENGTH] = {'N', 'o', 'N', 'e'};

const int MAX_NAME_LENGTH = 200;
const int MAX_SERNAME_LENGTH = 200;
const int MAX_PATRON_LENGTH = 200;
const int MAX_CURSE_LENGTH = 100;
const int MAX_GROUP_LENGTH = 100;

struct MenuItem {
    int id;
    char name;
    int hotkey;
    char description;
};

struct Terminal {
    int width;
    int height;
};

struct Point {
    int x;
    int y;
};

struct EditorState {
    int currentState;
    int insertState = 0;
    int commandState = 1;
    int queryState = 2;
};

struct View : Terminal {
    char **markup;
    char **editableZone;
    char **commandZone;
    int amountUsedBottomSpace;
    int amountUsedTopSpace;
    Point cursorPosition;
    Point logsLinePosition;
    Point commandLinePosition;
    Point insertZonePosition;
    EditorState editorState;
};


struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    char sername[MAX_SERNAME_LENGTH];
    int birthDate;
    char curse[MAX_CURSE_LENGTH];
    char group[MAX_GROUP_LENGTH];
    int firstMark;
    int secondMark;
    int thirdMark;
};


 
Terminal getTerminalProperties() {
    Terminal terminal;
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    terminal.width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    terminal.height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    terminal.width = (int)(w.ws_col);
    terminal.height = (int)(w.ws_row);
#endif // Windows/Linux
    return terminal;
}
 
void clear() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

void setCursor(Point point)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = point.x;
    coordinates.Y = point.y;
    SetConsoleCursorPosition ( handle , coordinates );
}

void hideScrollBar() {
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo; 

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
    COORD new_screen_buffer_size;
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - 
    screenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - 
    screenBufferInfo.srWindow.Top + 1; // Rows

    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

char keypress() {
    char c;
    c = getch();
    return c;
}

void preventResizing() {
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

MenuItem getNewNavItem(int id, char name, int hotkey, char description[] = DEFAULT_MENU_ITEM_DESCRIPTION) {
    MenuItem menuItem;
    menuItem.id = id;
    menuItem.name = name;
    menuItem.hotkey = hotkey;
    menuItem.description = name;
    return menuItem;
}

MenuItem* navigationFabric(char *navigationNames, int size) {
    MenuItem *menuItems = new MenuItem[size];
    for (int i = 0; i < size; i++) {
        MenuItem newNavItem = getNewNavItem(i, navigationNames[i], char(navigationNames[i]));
        menuItems[i] = newNavItem;
    }
    return menuItems;
}

View viewGenerateBaseMarkup(Terminal terminal) {
    View view;

    view.markup = new char*[terminal.height];

    view.width = terminal.width;
    view.height = terminal.height;

    for (int i = 0; i < terminal.height; i++) view.markup[i] = new char[terminal.width];

    // lets fill up this "matrix"
    for (int i = 0; i < terminal.height; i++) {
        for (int j = 0; j < terminal.width; j++) {
            char symbol = ' ';
            if (i == 0 && j < terminal.width || i == terminal.height - 1) {
                symbol = char(196); // -
            }
            if (j == 0 || j == terminal.width - 1) {
                symbol = char(179); // | 
            }
            view.markup[i][j] = symbol;
        }
    }

    view.markup[0][0] = char(218); 
    view.markup[0][terminal.width - 1] = char(191);
    view.markup[terminal.height - 1][terminal.width - 1] = char(217);
    view.markup[terminal.height - 1][0] = char(192);

    view.amountUsedBottomSpace = 1;
    view.amountUsedTopSpace = 1;

    return view;
}

void viewGenerateEditableZone(View &view) {
    int editableZoneHeight = view.height - view.amountUsedTopSpace - view.amountUsedBottomSpace;
    int editableZoneWidth =  view.width - 2;

    view.editableZone = new char*[editableZoneHeight];

    for (int i = 0; i < editableZoneHeight; i++) view.editableZone[i] = new char[editableZoneWidth];

    //! think about it
    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            if (i > view.amountUsedTopSpace - 1 && j != 0 && j != view.width - 1 && i < view.height - view.amountUsedBottomSpace - 1) {
                view.editableZone[i][j] = '@';
            }
        }
    }

    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            if (i > view.amountUsedTopSpace - 1 && j != 0 && j != view.width - 1 && i < view.height - view.amountUsedBottomSpace - 1) {
                view.editableZone[i][j] = '@';
            }
        }
    }

    view.insertZonePosition.x = 1;
    view.insertZonePosition.y = view.amountUsedTopSpace;
}

void viewGenerateMessageLine(View &view) {
    int messageLineHeight = 1;
    int messageLineBorder = view.amountUsedTopSpace + messageLineHeight;

    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            if (i == messageLineBorder) {
                view.markup[i][j] = char(196);
            }
        }
    }

    view.markup[messageLineBorder][0] = char(195);
    view.markup[messageLineBorder][view.width - 1] = char(180);

    view.amountUsedTopSpace += 2;
}

void viewGenerateCommandLine(View &view) {
    int commnadLineHeight = 2;
    int commandLineBorder = view.height - (view.amountUsedBottomSpace + commnadLineHeight); 

    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            if (i == commandLineBorder) {
                view.markup[i][j] = char(196);
            }
        }
    }
    view.markup[commandLineBorder][0] = char(195);
    view.markup[commandLineBorder][view.width - 1] = char(180);

    view.commandLinePosition.y = commandLineBorder + 1;
    view.commandLinePosition.x = 1;

    view.amountUsedBottomSpace += commnadLineHeight;
}

void viewGenerateSuggestions(View &view) {
    int menuHeight = 4;
    int menuStartLine = view.height - (view.amountUsedBottomSpace + menuHeight);
    int suggestionsLine = view.height - (view.amountUsedBottomSpace + 2);

    // \n - New записать новая запись в таблицу
    // \f - File вывод открыть файл + перемещение его в оперативку
    // \b - Binary открыть бинарник + перемещение его в оперативку
    // \a - All вывод ввиде таблицы
    // \w - Write запись в текстовый
    // \i - Insert запись в бинарник
    // \s - Search вывод по запросу
    // \r - Redo изменить запись
    // \d - Del удалить запись
    // \o - sOrt сортировать
    // \p - Plain text 
    // \c - Clear
    // \h - Help
    char navigationNames[] = {'n', 'f', 'b', 'a', 'w', 'i', 's', 'r', 'd', 'o', 'p', 'c', 'h'};
    int namesSize = sizeof(navigationNames) / sizeof(navigationNames[0]);
    MenuItem* navigationItems = navigationFabric(navigationNames, namesSize);

    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            if (i == menuStartLine) {
                view.markup[i][j] = char(196); // -
            }
        }
    }

    for (int j = 0, i = 0; i < view.width - 2; i++) {
        if (i % (int)ceil((view.width  - 2) / namesSize) == 0) {
            if (j >= namesSize) {
                break;
            }
            view.markup[suggestionsLine][i + 1] = '\\';
            view.markup[suggestionsLine][i + 2] = navigationItems[j].name;
            j++;
        }
    }

    view.markup[menuStartLine][0] = char(195);
    view.markup[menuStartLine][view.width - 1] = char(180);

    view.amountUsedBottomSpace += menuHeight;
}

void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    
    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}


void updateView(View view) {
    clear();

    char vm[3600 + 1] = {};

    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            vm[i * view.width + j] = view.markup[i][j];
        }
    }

    cout << vm;
}

void setCursorPositionByMode(View &view) {
    if (view.editorState.currentState == view.editorState.queryState) {
        view.cursorPosition = view.commandLinePosition;
    }
    if (view.editorState.currentState == view.editorState.insertState || view.editorState.currentState == view.editorState.commandState) {
        view.cursorPosition = view.insertZonePosition;
    }
    
    setCursor(view.cursorPosition);
}

void waitCmdCommand(View &view) {

    
}

#ifndef CTRL
#define CTRL(c) ((c) & 037)
#endif

void detectNextCursorPosition(View &view, char key) {
    if (0 < view.cursorPosition.x && view.cursorPosition.x < view.width - 1) {
        view.cursorPosition.x += 1;
    }
    setCursor(view.cursorPosition);
}

void commandKeyPressListener(View &view) {
    char key = keypress(); 

    if (view.editorState.currentState == view.editorState.commandState && key == ':') {
        view.editorState.currentState = view.editorState.queryState;
        setCursorPositionByMode(view);
    }
    else if (key == CTRL('[')) {
        view.editorState.currentState = view.editorState.commandState;
        setCursorPositionByMode(view);
    }
    else {
        view.editableZone[view.cursorPosition.y][view.cursorPosition.x] = key;
        updateView(view);
        detectNextCursorPosition(view, key);
    }



    commandKeyPressListener(view);
}


int main() {
    // hideScrollBar();
    preventResizing();

    Terminal terminal = getTerminalProperties();

    View view = viewGenerateBaseMarkup(terminal);

    viewGenerateSuggestions(view);
    viewGenerateCommandLine(view);
    viewGenerateMessageLine(view);
    viewGenerateEditableZone(view);

    view.editorState.currentState = view.editorState.commandState;

    updateView(view);

    setCursorPositionByMode(view);

    commandKeyPressListener(view);
    // waitCmdCommand(view);

    cout << "Logs: Here must be logs in production mode i will remove scroll(already relised)";

    return 0;
}