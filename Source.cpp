#include <iostream>
#include <Windows.h>
using namespace std;

// Written by Jorge Celaya, Credit to javidx9 - OneLoneCoder

int nScreenWidth = 120;
int nScreenHeight = 40;

float xPos = 0.0f;
float yPos = 0.0f;
float anglePos = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

int main() {
    // Create Screen Buffer
    wchar_t * screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
    
    wstring map;
    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";
    
    // game loop
    while(true) {
        for (int i=0; i<nScreenWidth; i++) {
            
        }
        
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
    }

    
    
    return 0;
}