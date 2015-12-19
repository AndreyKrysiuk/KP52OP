#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include "main.h"

void nullRobot(int size, struct ROBOT Robots[size]){
    int i;
    for(i = 0; i < size; i++){
    Robots[i].health = 800;
    Robots[i].accurracy = 0;
    Robots[i].damage = 0;
    Robots[i].defence = 0;
    Robots[i].range= 0;
    Robots[i].rate = 0;
    Robots[i].speed = 0;
    Robots[i].rank = 0;
    }
}
void printMenu(char * command[], int selected,  int size){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 3;
    pos.Y = 0;
    SetConsoleCursorPosition(hConsole, pos);
    int i;
    int colour;
    for(i = 0; i < size; i++){
        if(i == selected){
            colour = 0xEB;
            SetConsoleTextAttribute(hConsole, colour);
        } else {
            colour = 0x0F;
            SetConsoleTextAttribute(hConsole, colour);
        }
        printcommand(pos.X-3, pos.Y, 22, 5);
        pos.Y+=2;
        SetConsoleCursorPosition(hConsole, pos);
        printf("%s", command[i]);
        pos.Y+=3;
        SetConsoleCursorPosition(hConsole, pos);
        colour = 0x0F;
        SetConsoleTextAttribute(hConsole, colour);
    }
}
int menu(char * command[], int size, int numMenu){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = 0;
    int selected = 0;
    int num;
    int colour;
    while(TRUE){

    colour = 0x0F;
    SetConsoleTextAttribute(hConsole, colour);
    printMenu(command, selected, size);
    printcommand(62, 5, 35, 10);
    advantages(selected, numMenu);
     while (!kbhit()){
            bender(40,0);
            Sleep(250);
        }

    SetConsoleCursorPosition(hConsole, pos);
    num = getch();
    switch(num){
        case 119:
        case 87:
            if((selected > 0)){
            selected--;
            pos.Y--;
            }
            break;
        case 115:
        case 83:
            if((selected < size - 1)){
            selected++;
            pos.Y++;
            }
            break;
        case 13:
            selected = pos.Y;
            pos.X = 0;
            pos.Y = 5;
            SetConsoleCursorPosition(hConsole, pos);
            return selected;
        }
    }
}
void print(struct ROBOT * pRobots, int x, int y){
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD pos;
     pos.X = x;
     pos.Y = y;
     SetConsoleCursorPosition(hConsole, pos);
     pRobots->rank = pRobots->damage + pRobots->defence + pRobots->range + pRobots->speed +  pRobots->rate + pRobots->accurracy;
     printf("Nick: %s\n", pRobots->nickname);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Health: %i\n", pRobots->health);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Damage: %i\n", pRobots->damage);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Defence: %i\n", pRobots->defence);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Rate: %i\n", pRobots->rate);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Speed: %i\n", pRobots->speed);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Accurracy: %i\n", pRobots->accurracy);
     pos.Y++;
     SetConsoleCursorPosition(hConsole, pos);
     printf("Rank: %i\n", pRobots->rank);
}
void chooseWeapon(struct ROBOT * pRobots, int selected){
    switch(selected){
        case laserSMG:
            pRobots->damage = 75;
            pRobots->rate = 90;
            pRobots->accurracy += 75;
            break;
        case plasmaGun:
            pRobots->damage = 100;
            pRobots->rate = 50;
            pRobots->accurracy += 40;
            break;
        case railCannon:
            pRobots->damage = 90;
            pRobots->rate = 10;
            pRobots->accurracy += 100;
            break;
        case nanoDistructor:
            pRobots->damage = 100;
            pRobots->rate = 90;
            pRobots->accurracy += 75;
            break;
    }
}
void chooseArmor(struct ROBOT * pRobots, int selected){
    switch(selected){
        case powerT45:
            pRobots->health += 160;
            pRobots->defence += 80;
            break;
        case powerT51:
            pRobots->health += 180;
            pRobots->defence += 90;
            pRobots->speed -= 5;
            break;
        case powerT60:
            pRobots->health += 200;
            pRobots->defence += 100;
            pRobots->speed -= 10;
            break;
        case powerX01:
            pRobots->health += 150;
            pRobots->defence += 75;
            pRobots->speed += 5;
            break;
    }
}
void chooseVehicle(struct ROBOT * pRobots, int selected){
    switch(selected){
        case wheels:
            pRobots->speed += 90;
            pRobots->accurracy -= 5;
            break;
        case tracks:
            pRobots->health += 20;
            pRobots->defence += 10;
            pRobots->speed += 50;
            pRobots->accurracy += 30;
            break;
        case airscrews:
            pRobots->health -= 20;
            pRobots->defence -= 10;
            pRobots->speed += 100;
            pRobots->accurracy -= 10;
            break;
        case walkers:
            pRobots->health -= 10;
            pRobots->defence -= 5;
            pRobots->speed += 60;
            pRobots->accurracy += 30;
            break;
    }
}
void duel(struct ROBOT * Robot1, struct ROBOT * Robot2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    double chanceAvoid1;
    double chanceAvoid2;
    double chanceCreet1;
    double chanceCreet2;
    int health1 = Robot1->health;
    int health2 = Robot2->health;
    system("cls");
    printHealth(Robot1->nickname, health1, 0, 0);
    printHealth(Robot2->nickname, health2, 75, 0);
    printcommand(0, 34, 49, 5);
    printcommand(51, 34, 49, 5);
    while(health1 > 0 && health2 > 0){
            chanceAvoid1 = (double)(rand()%50)/100 + (double)Robot1->speed/1000;
            chanceAvoid2 = (double)(rand()%50)/100 + (double)Robot2->speed/1000;
            chanceCreet1 = (double)(rand()%50)/100 + (double)Robot1->accurracy/1000;
            chanceCreet2 = (double)(rand()%50)/100 + (double)Robot2->accurracy/1000;
            robot(3, 5, 1);
            robot(84, 5, 2);
            printShot(16, 12, 2);
            if(chanceAvoid1 > 0.5){
                printcommand(0, 34, 49, 5);
                pos.X = 2;
                pos.Y = 36;
                SetConsoleCursorPosition(hConsole, pos);
                printf("%s avoid a blow\n", Robot1->nickname);
                Sleep(500);
            } else if(chanceCreet2 > 0.5){
                health1 -= 2*Robot2->damage;
                printcommand(51, 34, 49, 5);
                pos.X = 53;
                pos.Y = 36;
                SetConsoleCursorPosition(hConsole, pos);
                printf("%s does a critical strike\n", Robot2->nickname);
                Sleep(500);
            } else {
                health1 -= Robot2->damage;
                printcommand(0, 34, 49, 5);
                pos.X = 2;
                pos.Y = 36;
                SetConsoleCursorPosition(hConsole, pos);
                printf("Takes %i damage", -Robot2->damage);
                Sleep(500);
            }
            printHealth(Robot1->nickname, health1, 0, 0);

            if(health1 > 0){
            printShot(16, 12, 1);
             if(chanceAvoid2 > 0.5){
                printcommand(51, 34, 49, 5);
                pos.X = 53;
                pos.Y = 36;
                SetConsoleCursorPosition(hConsole, pos);
                printf("%s avoid a blow\n", Robot2->nickname);
                Sleep(500);
            } else if(chanceCreet1 > 0.5){
                health2 -= 2*Robot1->damage;
                printcommand(0, 34, 49, 5);
                pos.X = 2;
                pos.Y = 36;
                SetConsoleCursorPosition(hConsole, pos);
                printf("%s does a critical strike\n", Robot1->nickname);
                Sleep(500);
            } else {
                health2 -= Robot1->damage;
                printcommand(51, 34, 49, 5);
                pos.X = 53;
                pos.Y = 36;
                SetConsoleCursorPosition(hConsole, pos);
                printf("Takes %i damage", -Robot1->damage);
                Sleep(500);
                    }
            }

            printHealth(Robot2->nickname, health2, 75, 0);
            if(health2 <= 0){
                    SetConsoleTextAttribute(hConsole, 0xEB);
                    printcommand(30, 15, 40, 5);
                    pos.X = 32;
                    pos.Y = 17;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("YOUR WINNER IS %s\n", Robot1->nickname);
                    SetConsoleTextAttribute(hConsole, 0x0F);
                    getch();
            }
            if(health1 <= 0){
                    SetConsoleTextAttribute(hConsole, 0xEB);
                    printcommand(30, 15, 40, 5);
                    pos.X = 32;
                    pos.Y = 17;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("YOUR WINNER IS %s\n", Robot2->nickname);
                    SetConsoleTextAttribute(hConsole, 0x0F);
                    getch();
            }
    }
    system("cls");
}
void loadGame(struct ROBOT * Robots){
    FILE * fp = fopen ("user.bin", "rb");
    fread(Robots, sizeof(struct ROBOT), 4, fp);
    fclose(fp);
}
void saveGame(struct ROBOT * Robots){
    FILE * fw = fopen ("user.bin", "wb");
    fwrite(Robots, sizeof(struct ROBOT), 4, fw);
    fclose(fw);
}
void createRobot(struct ROBOT * pRobots){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    char nickname[100];
    char * command1[] = {"Laser SMG", "Plasma Gun", "Rail Cannon", "Nano Distructor"};
    char * command2[] = {"Power T45", "Power T51", "Power T60", "Power X-01"};
    char * command3[] = {"Wheels", "Tracks", "Airscrews", "Walkers"};
    int size1 = sizeof(command1)/sizeof(int *);
    int size2 = sizeof(command2)/sizeof(int *);
    int size3 = sizeof(command3)/sizeof(int *);
    int check = 1;

    while(check != 0){
        system("cls");
        SetConsoleTextAttribute(hConsole, 0x0F);
        printcommand(0, 0, 25, 5);
        printcommand(62, 5, 30, 10);
        advantages(0,8);
        bender(40,0);
        pos.X = 2;
        pos.Y = 2;
        SetConsoleCursorPosition(hConsole, pos);
        gets(nickname);
        if(strlen(nickname) > 16){
            printcommand(62, 5, 30, 10);
            advantages(0, 6);
            Sleep(2000);
            check = 1;
        } else {
           check = 0;
        }
    }
    system("cls");
    strcpy(pRobots->nickname, nickname);
    chooseWeapon(pRobots, menu(command1, size1, 3));
    chooseArmor(pRobots, menu(command2, size2, 4));
    chooseVehicle(pRobots, menu(command3, size3, 5));
}
void printcommand(int x, int y, int length, int high){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    for(pos.Y = y; pos.Y < y + high; pos.Y++){
        for(pos.X = x; pos.X < (x + length); pos.X++){
            if(((pos.X == x) && (pos.Y == y)) || ((pos.X == x + length - 1) && (pos.Y == y + high - 1))
               || ((pos.X == x + length - 1) && (pos.Y == y)) || ((pos.X == x) && (pos.Y == y + high - 1))){
                SetConsoleCursorPosition(hConsole, pos);
                printf("#");
            } else if((pos.Y == y) || (pos.Y == y + high - 1)){
                SetConsoleCursorPosition(hConsole, pos);
                printf("=");
            } else if((pos.X == x) || (pos.X == x + length - 1)) {
                SetConsoleCursorPosition(hConsole, pos);
                printf("|");
            } else {
                SetConsoleCursorPosition(hConsole, pos);
                printf(" ");
            }
        }
    }
}
void bender(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    FILE * fp;
    char str[23];
    int i;
    int flash = rand()%2;
    fp = fopen("bender.txt", "r");
    if (NULL == fp) {
        exit(EXIT_FAILURE);
    }
    while(!feof(fp)){
        fgets(str, 23, fp);
        for(i = 0; i < 21; i++){
        switch(str[i]){
            case '0':
            case '5':
                SetConsoleTextAttribute(hConsole, 0x0F); //чЄрный
                break;
            case '6':
                if(flash == 1){
                SetConsoleTextAttribute(hConsole, 0xEF); //€рко-желтый
                } else {
                SetConsoleTextAttribute(hConsole, 0x6F);
                }
                break;
            case '7':
                if(flash == 1){
                SetConsoleTextAttribute(hConsole, 0x6F); //€рко-желтый
                } else {
                SetConsoleTextAttribute(hConsole, 0xEF);
                }
                break;
            case '3':
                SetConsoleTextAttribute(hConsole, 0x8F); //темно-серый
                break;
            case '1':
                SetConsoleTextAttribute(hConsole, 0x1F); //фиолетовй
                break;
            case '4':
            case '2':
                SetConsoleTextAttribute(hConsole, 0x7F); //серый
                break;
            case '8':
                SetConsoleTextAttribute(hConsole, 0xEF); //€рко-желтый
                break;
            }
            printf(" ");
        }
        printf("\n");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
    }
    fclose(fp);
}
void robot(int x, int y, int state){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    FILE * fp;
    char str[15];
    int i;
    if(state == 1){
        fp = fopen("robot1.txt", "r");
    } else {
        fp = fopen("robot2.txt", "r");
    }
    if (NULL == fp) {
        exit(EXIT_FAILURE);
    }
    while(!feof(fp)){
        fgets(str, 15, fp);
        for(i = 0; i < 13; i++){
        switch(str[i]){
            case '0':
                SetConsoleTextAttribute(hConsole, 0x0F);
                break;
            case '5':
                if(state == 1){
                    SetConsoleTextAttribute(hConsole, 0x4F);
                } else {
                    SetConsoleTextAttribute(hConsole, 0x3F);
                }
                break;
            case '1':
                if(state == 1){
                    SetConsoleTextAttribute(hConsole, 0xCF);
                } else {
                    SetConsoleTextAttribute(hConsole, 0xBF);
                }
                break;
            case '2':
                SetConsoleTextAttribute(hConsole, 0x8F);
                break;
            case '3':
                SetConsoleTextAttribute(hConsole, 0x7F);
                break;
            case '4':
                SetConsoleTextAttribute(hConsole, 0xEF);
                break;
            }
            printf(" ");
        }
        printf("\n");
        pos.Y++;
        SetConsoleCursorPosition(hConsole, pos);
    }
    fclose(fp);
}
void printRating(int size, struct ROBOT Robots[size]){
    system("cls");
    int count = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = 0;
    SetConsoleTextAttribute(hConsole, 0x0F);
    for(count = 0; count < size; count++){
        printcommand(pos.X, pos.Y, 25, 10);
        SetConsoleCursorPosition(hConsole, pos);
        print(&Robots[count], pos.X+1, pos.Y+1);
        pos.X+=25.;
        SetConsoleCursorPosition(hConsole, pos);
    }
    pos.X = 0;
    pos.Y = 12;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Press any key to continue");
    getch();
    system("cls");
}
void printShot(int x, int y, int state){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int coorX;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    if(state == 1){
        for(coorX = x; coorX < x + 67; coorX++){
            pos.X = coorX;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, 0xC0);
            printf(" ");
            Sleep(35);
            pos.X = coorX;
            SetConsoleTextAttribute(hConsole, 0x00);
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
            Sleep(10);
            SetConsoleTextAttribute(hConsole, 0x0F);
            }
        }
     if(state == 2){
            for(coorX = x + 67; coorX > x; coorX--){
                pos.X = coorX;
                SetConsoleCursorPosition(hConsole, pos);
                SetConsoleTextAttribute(hConsole, 0xB0);
                printf(" ");
                Sleep(25);
                pos.X = coorX;
                SetConsoleTextAttribute(hConsole, 0x00);
                SetConsoleCursorPosition(hConsole, pos);
                printf(" ");
                Sleep(10);
                SetConsoleTextAttribute(hConsole, 0x0F);
        }
    }
}
void printHealth(char * nick, int health, int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
    printcommand(pos.X, pos.Y, 25, 3);
    pos.X = x + 1;
    pos.Y = y + 1;
    SetConsoleCursorPosition(hConsole, pos);
    if(health > 0){
        printf("%s: %i", nick, health);
    } else {
        printf("%s: 0", nick);
    }
}
void advantages(int selected, int numMenu){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 64;
    pos.Y = 6;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, 0x0A);
    switch(numMenu){
        case 0:
            switch(selected){
            case 0:
                printf("Hello! I'm Bender!");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("You play in MY game!!!");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("So...You can begin a new game,");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("create four new robots");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("and make them fight, fight");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("aaand...FIGHT!!!");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("P.S. Use 'W' and 'S' to move.");
                break;
            case 1:
                printf("You can load last played game.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("It contains four robots,");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("that ready to new FIGHT!!!");
                break;
            case 2:
                printf("It's easy.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("Just save your game,");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("When you want it.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("Don't forget save before exit!");
                break;
            case 3:
                printf("If you want...Go...");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("If you really want it...");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("I want to spend time with you...");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("P.S.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("DON'T PRESS THIS KEY, HUMAN!!!");
                break;
                break;
                }
            break;
        case 1:
            switch(selected){
            case 0:
                printf("Create a new robot.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("Give him a name.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("Choose weapon,armor and vehicle!");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("You can create only four robot!");
                break;
            case 1:
                printf("Show you rating table");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("for created  robots.");
                break;
            case 2:
                printf("Choose two robots");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("and make them fight");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("with each other.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("It's really funny, human!");
                break;
            case 3:
                printf("Just returns you to main menu.");
                break;
            }
            break;
        case 2:
            switch(selected){
            case 0:
                printf("Show you rating table");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("for created robots.");
                break;
            case 1:
                printf("Choose two robots");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("and make them fight");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("with each other.");
                pos.Y++;
                SetConsoleCursorPosition(hConsole, pos);
                printf("It's really funny, human!");
                break;
            case 2:
                printf("Just returns you to main menu.");
                break;
            }
            break;
        case 3:
            switch(selected){
                case 0:
                    printf("Choose your weapon, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Laser SMG");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Damage: +75");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Rate: +90");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: +75");
                    break;
                case 1:
                    printf("Choose your weapon, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Plasma Gun");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Damage: +100");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Rate: +50");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: +40");
                    break;
                case 2:
                     printf("Choose your weapon, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Rain Cannon");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Damage: +90");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Rate: +10");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: +100");
                    break;
                case 3:
                     printf("Choose your weapon, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Nano Distructor");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Damage: +100");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Rate: +90");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: +75");
                    break;
            }
            break;
        case 4:
            switch(selected){
                case 0:
                    printf("Choose your armor, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Power T45");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: +160");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: +80");
                    break;
                case 1:
                    printf("Choose your armor, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Power T51");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: +180");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: +90");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: -5");
                    break;
                case 2:
                         printf("Choose your armor, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Power T60");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: +200");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: +100");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: -10");
                    break;
                case 3:
                    printf("Choose your armor, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Power X-01");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: +150");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: +75");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: +5");
                    break;
            }
            break;
        case 5:
            switch(selected){
                case 0:
                    printf("Choose your vehicle, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Wheels");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: +90");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: -5");
                    break;
                case 1:
                    printf("Choose your vehicle, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Tracks");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: +20");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: +10");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: +50");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: +30");
                    break;
                case 2:
                    printf("Choose your vehicle, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Aircrews");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: -20");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: -10");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: +100");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: -10");
                    break;
                case 3:
                    printf("Choose your vehicle, human!");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Walkers");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Health: -10");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Defence: -5");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Speed: +60");
                    pos.Y++;
                    SetConsoleCursorPosition(hConsole, pos);
                    printf("Accurracy: +30");
                    break;
            }
            break;
        case 6:
            printf("Your nickname is too long.");
            pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
            printf("Think up something shorter.");
            break;
        case 7:
            printf("Choose your fighters!");
            pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
            printf("And let battle begin!");
            break;
        case 8:
            printf("Give a name for your robot.");
            pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
            printf("Zoidberg.....");
            pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
            printf("Fray.....");
            pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
          printf("Use your imagination...");
             pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
            printf("P.S. Less than 16 symbols");

            break;
        case 9:
            printf("Maximum number of robots");
            pos.Y++;
            SetConsoleCursorPosition(hConsole, pos);
            printf("P.S. Stop, crazy human!");
            break;
        case 10:
            printf("Maybe you first create a robot?");
            break;
        case 11:
            printf("Okay, your game is saved.");
            break;
        case 12:
            printf("Goodbye, Human!");
            break;
        case 13:
            printf("Create 4 robots to fight");
            break;
    }
}
