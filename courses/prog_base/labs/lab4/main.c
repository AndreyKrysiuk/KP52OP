#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "main.h"

int main()
{
    struct ROBOT Robots[4];
    int i;
    int backMenu = 0;
    int countRobot = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    char * commandMenu[] = {"NEW GAME", "LOAD GAME", "SAVE GAME", "EXIT"};
    char * menuNew[] = {"CREATE ROBOT", "RATING", "DUEL", "BACK TO MENU"};
    char * menuLoad[] = {"RATING", "DUEL", "BACK TO MENU"};
    char * robotList[4];
    int sizeMenu = sizeof(commandMenu)/sizeof(int *);
    int sizeMenuNew = sizeof(menuNew)/sizeof(int*);
    int sizeMenuLoad = sizeof(menuLoad)/sizeof(int*);
    int sizeRobotList;
    while(1){
    backMenu = 0;
    switch(menu(commandMenu, sizeMenu, 0)){
        case 0:
            system("cls");
            nullRobot(4, Robots);
            while(backMenu == 0){
                switch(menu(menuNew, sizeMenuNew, 1)){
                    case 0:
                        if(countRobot < 4){
                            createRobot(&Robots[countRobot]);
                            countRobot++;
                            break;
                        } else {
                            SetConsoleTextAttribute(hConsole, 0x0F);
                            printcommand(62, 5, 35, 10);
                            advantages(0, 9);
                            Sleep(2000);
                            break;
                        }
                    case 1:
                        if(countRobot == 0){
                            printcommand(62, 5, 35, 10);
                            advantages(0, 10);
                            Sleep(2000);
                        } else {
                        printRating(countRobot, Robots);
                        }
                        break;
                    case 2:
                        if(countRobot <= 3){
                            printcommand(62, 5, 35, 10);
                            advantages(0, 13);
                            Sleep(2000);
                        } else {
                        for(i = 0; i < countRobot; i++){
                            robotList[i] = Robots[i].nickname;
                        }
                        sizeRobotList = sizeof(robotList)/sizeof(int*);
                        duel(&Robots[menu(robotList, sizeRobotList, 7 )], &Robots[menu(robotList, sizeRobotList,7)]);
                        system("cls");
                        break;
                    case 3:
                        backMenu = 1;
                        system("cls");
                        break;
                    }
                }
            }
            break;
        case 1:
            system("cls");
            loadGame(Robots);
                while(backMenu == 0){
                    switch(menu(menuLoad, sizeMenuLoad, 2)){
                        case 0:
                            system("cls");
                            printRating(4, Robots);
                            break;
                        case 1:
                            for(i = 0; i < 4; i++){
                            robotList[i] = Robots[i].nickname;
                            }
                            sizeRobotList = sizeof(robotList)/sizeof(int*);
                            duel(&Robots[menu(robotList, sizeRobotList, 7)], &Robots[menu(robotList, sizeRobotList, 7)]);
                            break;
                        case 2:
                            backMenu = 1;
                            break;
                        }
                }
                break;
        case 2:
            saveGame(Robots);
            printcommand(62, 5, 35, 10);
            advantages(0, 11);
            Sleep(4000);
            break;
        case 3:

            printcommand(62, 5, 35, 10);
            advantages(0, 12);
            SetConsoleTextAttribute(hConsole, 0x0F);
            pos.X = 0;
            pos.Y = 35;
            SetConsoleCursorPosition(hConsole, pos);
            exit(EXIT_SUCCESS);
            break;
            }
    }
}



