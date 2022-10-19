#include<iostream>
#include<math.h>
#include<cmath>
#include <winuser.h>
#include <functional>
 
#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
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

struct View : Terminal {
    char **markup;
    char **editableZone;
    char **commandZone;
    Point cursorPosition;
    int amountUsedBottomSpace;
    int amountUsedTopSpace;
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

void setCursor(int x = 0 , int y = 0)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
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
    system ("/bin/stty raw");
    char c;
    system("/bin/stty -echo");
    c = getc(stdin);
    system("/bin/stty echo");
    system ("/bin/stty cooked");
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
        char *row = new char[terminal.width];
        for (int j = 0; j < terminal.width; j++) {
            char symbol = ' ';
            if (i == 0 && j < terminal.width || i == terminal.height - 1) {
                symbol = char(196); // -
            }
            if (j == 0 || j == terminal.width - 1) {
                symbol = char(179); // | 
            }
            row[j] = symbol;
        }
        view.markup[i] = row;
    }

    view.markup[0][0] = char(218); 
    view.markup[0][terminal.width - 1] = char(191);
    view.markup[terminal.height - 1][terminal.width - 1] = char(217);
    view.markup[terminal.height - 1][0] = char(192);

    view.amountUsedBottomSpace = 1;
    view.amountUsedTopSpace = 1;

    return view;
}

void viewDisplayEditableZone(View &view) {
    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
        }
    }
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

// void commands() {



//     int height = terminal.height;
//     int width = terminal.width;
// }

void updateView(View view) {
    clear();

    // this fucking boolshit has to be changed
    for (int i = 0; i < view.height; i++) {
        for (int j = 0; j < view.width; j++) {
            cout << view.markup[i][j];
        }
    }

}

int main() {
    // hideScrollBar();
    preventResizing();

    Terminal terminal = getTerminalProperties();

    View view = viewGenerateBaseMarkup(terminal);

    viewGenerateSuggestions(view);
    viewGenerateCommandLine(view);
    viewGenerateMessageLine(view);

    updateView(view);

    cout << "Logs: Here must be logs in production mode i will remove scroll(already relised)";

    setCursor(1, 1);

    getchar();

    return 0;
}