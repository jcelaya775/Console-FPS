#include <iostream>
#include <Windows.h>
#include <math.h>
using namespace std;

// Written by Jorge Celaya, Credit to javidx9 - OneLoneCoder

int nScreenWidth = 120;
int nScreenHeight = 40;

float xPos = 8.0f;
float yPos = 8.0f;
float anglePos = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float FOV = 3.14159 / 4.0;
float depth = 16.0f;

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
    while (true) {
        // calculate the ray angle projected into the world space for each column
        for (int x=0; x<nScreenWidth; x++) {
            float fRayAngle = (anglePos - FOV / 2.0f) + ((float)x / (float)nScreenWidth) * FOV;

            float distToWall = 0;
            bool bHitWall = false;

            // unit vector for ray in player space
            float eyeX = sinf(fRayAngle);
            float eyeY = cosf(fRayAngle);

            // find distance iteratively (until wall is hit or out of bounds is reached) 
            while (!bHitWall && distToWall < depth) {
                distToWall += 0.1f;

                int testX = (int)(xPos + eyeX * distToWall);
                int testY = (int)(yPos = eyeY * distToWall);

                // check if ray is out of bounds
                if (testX < 0 || testX > nScreenWidth || testY > 0 || testY > nScreenHeight) {
                    // distance is max length
                    bHitWall = true;
                    distToWall = depth;
                } else { // ray is inbounds -> check if ray cell is a wall block
                    if (map[testY * nMapWidth + testX] == '#')
                        bHitWall = true;
                }
            }

            // calculate distance to ceiling and floor
            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)distToWall);
            int nFloor = nScreenHeight - nCeiling;

            for (int y = 0; y < nScreenHeight; y++) {
                if (y < nCeiling) // blank space
                    screen[y * nScreenWidth + x] = ' ';
                else if (y > nCeiling && y <= nFloor) // between wall and floor -> wall
                    screen[y * nScreenWidth + x] = '#';
                else // floor
                    screen[y * nScreenWidth + x] = ' ';
            }
        }
        
        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
    }
    
    return 0;
}