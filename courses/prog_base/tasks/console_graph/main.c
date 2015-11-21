#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

void graph1(int startX, int StartY, float n);
void graph2(int startX, int StartY, float n);
void printDec(int startX, int StartY);
void print_graph1();
void print_graph2();

int main()
{
        float fmt;
        int command;
        int checkexit = 0;
        int startX = 39;
        int startY = 12;
        int current_graph = 1;
        float n = 1;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        printDec(startX, startY);
        print_graph1();
        graph1(startX, startY, n);


        while(checkexit != 1){
           command = getch();
           switch(command){
               case 113:
                    fmt = 0x07;
                    SetConsoleTextAttribute(hConsole, fmt);
                    system("cls");
                    printDec(startX, startY);
                    current_graph = 2;
                    print_graph2();
                    graph2(startX, startY, n);
                    break;
                case 114:
                    fmt = 0x07;
                    SetConsoleTextAttribute(hConsole, fmt);
                    system("cls");
                    printDec(startX, startY);
                    current_graph = 1;
                    print_graph1();
                    graph1(startX, startY, n);
                    break;
                case 119:
                    if(startY > 0){
                        startY--;
                        if(current_graph == 1){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph1();
                            graph1(startX, startY, n);
                        }
                        if(current_graph == 2){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph2();
                            graph2(startX, startY, n);
                        }
                    }
                    break;
                case 97:
                    if(startX > 0){
                        startX--;
                        if(current_graph == 1){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph1();
                            graph1(startX, startY, n);
                        }
                        if(current_graph == 2){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph2();
                            graph2(startX, startY, n);
                        }
                    }
                    break;
                case 115:
                    if(startY < 24){
                        startY++;
                        if(current_graph == 1){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph1();
                            graph1(startX, startY, n);
                        }
                        if(current_graph == 2){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph2();
                            graph2(startX, startY, n);
                        }
                    }
                    break;
                case 100:
                    if(startX < 79){
                        startX++;
                        if(current_graph == 1){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph1();
                            graph1(startX, startY, n);
                        }
                        if(current_graph == 2){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph2();
                            graph2(startX, startY, n);
                        }
                    }
                    break;
                case 45:
                        n += 0.1;
                        if(current_graph == 1){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph1();
                            graph1(startX, startY, n);
                        }
                        if(current_graph == 2){
                            fmt = 0x07;
                            SetConsoleTextAttribute(hConsole, fmt);
                            system("cls");
                            printDec(startX, startY);
                            print_graph2();
                            graph2(startX, startY, n);
                        }
                        break;
                case 43:
                        n -= 0.1;
                        if(n >= 0.1){
                            if(current_graph == 1){
                                fmt = 0x07;
                                SetConsoleTextAttribute(hConsole, fmt);
                                system("cls");
                                printDec(startX, startY);
                                print_graph1();
                                graph1(startX, startY, n);
                            }
                            if(current_graph == 2){
                                fmt = 0x07;
                                SetConsoleTextAttribute(hConsole, fmt);
                                system("cls");
                                printDec(startX, startY);
                                print_graph2();
                                graph2(startX, startY, n);
                            }
                        }
                        break;

                case 101:
                    checkexit = 1;
                    break;
           }

        }

        fmt = 0x07;
        SetConsoleTextAttribute(hConsole, fmt);
        pos.X = 0;
        pos.Y = 26;
        SetConsoleCursorPosition(hConsole, pos);
        return 0;
}

void graph1(int startX, int startY, float n){
     int fmt;
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     int x, y;
     fmt = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
     SetConsoleTextAttribute(hConsole, fmt);
      for (x = -39; x < 39; x++)
    {
        y = n*(pow(n*x,2) + 3);
        pos.X = startX + x;
        pos.Y = startY - y;
        if((pos.Y < 25) && (pos.Y >= 0) && (pos.X >= 0) && (pos.X < 80)){
        SetConsoleCursorPosition(hConsole, pos);
        printf(" ");
        }
    }

}

void graph2(int startX, int startY, float n){
     int fmt;
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     int x, y;
     fmt = BACKGROUND_RED | BACKGROUND_INTENSITY;
     SetConsoleTextAttribute(hConsole, fmt);
      for (x = -78; x < 78; x++)
    {
        y = n*(tan(n*x + 2) + 2);
        pos.X = startX + x;
        pos.Y = startY - y;
        if((pos.Y < 25) && (pos.Y >= 0) && (pos.X >= 0 ) && (pos.X < 80)){
        SetConsoleCursorPosition(hConsole, pos);
        printf(" ");
        }
    }

}

void printDec(int startX, int startY){
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = startX;
        pos.Y = startY;
        SetConsoleCursorPosition(hConsole, pos);
        printf("+");
        for(pos.X = 0; pos.X < startX; pos.X++){
            SetConsoleCursorPosition(hConsole, pos);
            printf("-");
        }
        for(pos.X = startX + 1; pos.X < 80; pos.X++){
            SetConsoleCursorPosition(hConsole, pos);
            printf("-");
        }
        for(pos.X = startX, pos.Y = 0; pos.Y < startY; pos.Y++){
            SetConsoleCursorPosition(hConsole, pos);
            printf("|");
        }
         for(pos.X = startX, pos.Y = startY+1; pos.Y < 25; pos.Y++){
            SetConsoleCursorPosition(hConsole, pos);
            printf("|");
        }
}

void print_graph1(){
     int fmt = 0x07;
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     pos.X = 0;
     pos.Y = 24;
     SetConsoleTextAttribute(hConsole, fmt);
     SetConsoleCursorPosition(hConsole, pos);
     printf("y = x^2 + 3\n");
     printf("R - GRAPH1; Q - GRAPH2; WASD - MOVE; +/- ZOOM; E - EXIT");
}

void print_graph2(){
     int fmt = 0x07;
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     pos.X = 0;
     pos.Y = 24;
     SetConsoleTextAttribute(hConsole, fmt);
     SetConsoleCursorPosition(hConsole, pos);
     printf("y = tan(x + 2) + 2\n");
     printf("R - GRAPH1; Q - GRAPH2; WASD - MOVE; +/- ZOOM; E - EXIT");
}

