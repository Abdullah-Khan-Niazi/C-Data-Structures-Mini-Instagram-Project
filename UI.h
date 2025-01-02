#include <iostream>
#include <string>
#include <windows.h>
#include<vector>
using namespace std;
class UI {
public:
    static int getConsoleWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
        return 80;
    }
    static void printCentered(const string& text, char fill = ' ') {
        int consoleWidth = getConsoleWidth();
        int padding = (consoleWidth - static_cast<int>(text.size())) / 2;
        if (padding > 0) {
            cout << string(padding, fill);
        }
        cout << text << endl;
    }
    static void printTitle(const string& title, char border = '=') {
        int consoleWidth = getConsoleWidth();
        string borderLine(consoleWidth, border);
        cout << borderLine << endl;
        printCentered(title, ' ');
        cout << borderLine << endl;
    }
    static void printSeparator(char separator = '-') {
        int consoleWidth = getConsoleWidth();
        cout << string(consoleWidth, separator) << endl;
    }
    static void printOptions(const string options[], int size) {
        for (int i = 0; i < size; ++i) {
            cout << "[" << (i + 1) << "] " << options[i] << endl;
        }
    }
    static void printBoxed(const string& message, char border = '*') {
        int consoleWidth = getConsoleWidth();
        vector<string> lines;
        size_t start = 0, end;
        while ((end = message.find('\n', start)) != string::npos) {
            lines.push_back(message.substr(start, end - start));
            start = end + 1;
        }
        lines.push_back(message.substr(start)); 
        size_t maxLineWidth = 0;
        for (const string& line : lines) {
            maxLineWidth = max(maxLineWidth, line.size());
        }
        int boxWidth = static_cast<int>(maxLineWidth) + 4;
        int padding = (consoleWidth - boxWidth) / 2;
        if (padding > 0) {
            cout << string(padding, ' ');
        }
        cout << string(boxWidth, border) << endl;
        for (const string& line : lines) {
            if (padding > 0) {
                cout << string(padding, ' ');
            }
            cout << border << " " << line;
            cout << string(maxLineWidth - line.size(), ' ') << " " << border << endl;
        }
        if (padding > 0) {
            cout << string(padding, ' ');
        }
        cout << string(boxWidth, border) << endl;
    }
    void clear() {
        system("cls");
    }
    void delay(int x) {
        Sleep(x);
    }
    void LoadScreen() {
        printTitle("INSTAGRAM CONSOLE APPLICATION");
        cout << endl;
        printCentered("        .:-=====++++++++=====--.        ");
        printCentered("     =#@@@@@@@@@@@@@@@@@@@@@@@@@@#=     ");
        printCentered("   =@@@@*=--:::::::::::::::::-=*@@@@+   ");
        printCentered("  *@@@=                       .  -@@@%  ");
        printCentered(" =@@@.                      *@@@: .@@@+ ");
        printCentered(" #@@*          -+#%%%%#+-   +@@%:  +@@@ ");
        printCentered(" %@@=        +@@@@@%%@@@@@*.       -@@@ ");
        printCentered(" @@@=      -@@@%=.     -#@@@=      -@@@ ");
        printCentered(" @@@=     .@@@+          =@@@:     :@@@ ");
        printCentered(" @@@-     *@@%            *@@#     :@@@ ");
        printCentered(" @@@-     *@@%            *@@#     :@@@ ");
        printCentered(" @@@=     :@@@=          -@@@-     :@@@ ");
        printCentered(" @@@=      -@@@#-      :#@@@+      -@@@ ");
        printCentered(" %@@=       .*@@@@%##%@@@@#:       -@@@ ");
        printCentered(" #@@*          -+#%%%%#*-.         +@@@ ");
        printCentered(" =@@@.                            .@@@+ ");
        printCentered("  #@@@-                          :%@@%  ");
        printCentered("   +@@@%*=::................::-+%@@@*   ");
        printCentered("    .+%@@@@@@@@@@@@@@@@@@@@@@@@@@%+.    ");
        printCentered("        :-==++++++++++++++++==-:         ");
        cout << endl;
        printBoxed("Developed By : \n               Abdullah Niazi(23F0017) \n               Muhammad Ahmad(23F0022)");
        Sleep(2000);
    }
};



