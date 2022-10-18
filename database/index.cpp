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
 
void getTerminalSize(int& width, int& height) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
#endif // Windows/Linux
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

int[] getWindowSize() {
    int width=0, height=0;
    getTerminalSize(width, height);

}

void commands() {

    char view[MAX_MARKUP_SIZE][MAX_MARKUP_SIZE] = {};

    int menuStartLine = height - 5;
    int suggestionsLine = height - 3;
    int commandLine = height - 7;
}

void updateView(int t) {
    clear();
    hideScrollBar();
    preventResizing();
    


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

    // lets fill up this "matrix"
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char symbol = *" ";
            if (i == 0 && j < width || i == height - 1) {
                symbol = char(196); // -
            }
            if (j == 0 || j == width - 1) {
                symbol = char(179); // | 
            }
            if (i == menuStartLine) {
                symbol = char(196); // -
            }
            if (i == commandLine) {
                symbol = char(196); // -
            }
            view[i][j] = symbol;
        }
    }

    for (int j = 0, i = 0; i < width - 2; i++) {
        if (i % (int)ceil((width  - 2) / namesSize) == 0) {
            if (j >= namesSize) {
                break;
            }
            view[suggestionsLine][i + 1] = '\\';
            view[suggestionsLine][i + 2] = navigationItems[j].name;
            j++;
        }
    }

    view[0][0] = char(218); 
    view[0][width - 1] = char(191);
    view[height - 1][width - 1] = char(217);
    view[height - 1][0] = char(192);

    view[menuStartLine][0] = char(195);
    view[menuStartLine][width - 1] = char(180);

    view[commandLine][0] = char(195);
    view[commandLine][width - 1] = char(180);

    for (int i = 0; i < height; i++) {
        cout << view[i];
    }

    setCursor(1, commandLine + 1);

    getchar();
}

int main() {
    // and we will user this matrix for changes observing
    updateView(0);
    return 0;
}