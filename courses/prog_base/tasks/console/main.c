#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int getColour(int x){
    int fmt;
                 switch(x){
                case 0:
                fmt = BACKGROUND_RED | BACKGROUND_BLUE |BACKGROUND_INTENSITY;
                break;
                case 1:
                fmt = BACKGROUND_RED | BACKGROUND_GREEN |BACKGROUND_INTENSITY;
                break;
                case 2:
                fmt = BACKGROUND_RED | BACKGROUND_INTENSITY;
                break;
                }
                return fmt;
}

int main()
{
    const long SLEEP_MILLISECONDS = 5;
    int fmt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = 0;
        pos.Y = 24;

    SetConsoleCursorPosition(hConsole, pos);
    Sleep(SLEEP_MILLISECONDS);

        fmt = BACKGROUND_RED | BACKGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, fmt);
        printf("*");

        while(pos.X<79){
            if(pos.X==0){
                 switch(pos.Y%3){
                case 0:
                fmt = BACKGROUND_RED | BACKGROUND_BLUE  |BACKGROUND_INTENSITY;
                break;
                case 1:
                fmt = BACKGROUND_RED  |BACKGROUND_INTENSITY;
                break;
                case 2:
                fmt = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
                break;
                }
                 SetConsoleTextAttribute(hConsole, fmt);
                --pos.Y;
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                while(pos.Y<24){
                    pos.X++;
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    Sleep(SLEEP_MILLISECONDS);
                    printf("*");
                }
            }
        if(pos.Y==24){
                if(pos.X<50){
                fmt=getColour(pos.X%3);
                } else {
                    switch(pos.X%3){
                case 0:
                fmt = BACKGROUND_RED | BACKGROUND_INTENSITY;
                break;
                case 1:
                fmt = BACKGROUND_RED | BACKGROUND_GREEN  |BACKGROUND_INTENSITY;
                break;
                case 2:
                fmt = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
                break;
                }
            }
                SetConsoleTextAttribute(hConsole, fmt);
                ++pos.X;
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                while((pos.Y>0)&&(pos.X>0)){
                    pos.X--;
                    pos.Y--;
                    SetConsoleCursorPosition(hConsole, pos);
                    Sleep(SLEEP_MILLISECONDS);
                    printf("*");
                }
            }
        if(pos.Y==0){
                if(pos.X<30){
                fmt=getColour(pos.X%3);
                } else {
                switch(pos.X%3){
                case 0:
                fmt = BACKGROUND_RED | BACKGROUND_INTENSITY;
                break;
                case 1:
                fmt = BACKGROUND_RED | BACKGROUND_GREEN  |BACKGROUND_INTENSITY;
                break;
                case 2:
                fmt = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
                break;
                }
            }
                SetConsoleTextAttribute(hConsole, fmt);
                ++pos.X;
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                while((pos.Y<24)&&(pos.X<79)){
                    pos.X++;
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    Sleep(SLEEP_MILLISECONDS);
                    printf("*");
                }
            }
            if((pos.Y==0)&&(pos.X==79))
                break;
            if((pos.X==79)){
                    if(pos.X<78){
                fmt=getColour(pos.X%3);
                SetConsoleTextAttribute(hConsole, fmt);
            } else {
                switch(pos.Y%3){
                case 0:
                fmt = BACKGROUND_RED | BACKGROUND_GREEN |BACKGROUND_INTENSITY;
                break;
                case 1:
                fmt = BACKGROUND_RED| BACKGROUND_INTENSITY;
                break;
                case 2:
                fmt = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
                break;
                }
                SetConsoleTextAttribute(hConsole, fmt);
            }
                --pos.Y;
                SetConsoleCursorPosition(hConsole, pos);
                Sleep(SLEEP_MILLISECONDS);
                printf("*");
                while((pos.Y>0)&&(pos.X>0)){
                    pos.X--;
                    pos.Y--;
                    SetConsoleCursorPosition(hConsole, pos);
                    Sleep(SLEEP_MILLISECONDS);
                    printf("*");
                }
            }

        }
        fmt = BACKGROUND_INTENSITY;
        SetConsoleTextAttribute(hConsole, fmt);
        pos.X = 0;
        pos.Y = 26;
        SetConsoleCursorPosition(hConsole, pos);
        return 0;
}
