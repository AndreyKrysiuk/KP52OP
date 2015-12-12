#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>

struct FOUNDERS{
    char nameFounder[30];
    time_t ageFounder;
};
struct STARTUP{
    char nameStartUp[30];
    char * nameFounder;
    int investments;
};

int main()
{

}

void standartStruct1(struct FOUNDERS * pFounder){
    strcpy(pFounder->nameFounder, "Darth Weider");
    struct tm * pTime = (struct tm *)malloc(sizeof(struct tm));
    pTime->tm_mday = 1;
    pTime->tm_mon  = 1;
    pTime->tm_year = 50;
    pTime->tm_hour = 12;
    pTime->tm_min  = 12;
    pTime->tm_sec  = 12;
    pFounder->ageFounder = mktime(pTime);
}

void standartStruct2(struct STARTUP * pStartup){
    strcpy(pStartup->nameStartUp,"Death Star");
    pStartup->nameFounder = "Darth Weider";
    pStartup->investments = 100000000;
}

void printStruct1(struct FOUNDERS * pFounder){
    printf("Name of Founder: %s\n", pFounder->nameFounder);
    printf("Date of Birth: %s\n", ctime(&(pFounder->ageFounder)));
}

void printStruct2(struct STARTUP * pStartup){
    printf("Name of StartUp: %s\n", pStartup->nameStartUp);
    printf("Name of Founder: %s\n", pStartup->nameFounder);
    printf("Investments: %i\n", pStartup->investments);
}

struct FOUNDERS * memStruct1(){
    struct FOUNDERS * pFounder = malloc(sizeof(struct FOUNDERS));
    return pFounder;
}

struct STARTUP * memStruct2(){
    struct STARTUP * pStartup = malloc(sizeof(struct STARTUP));
    return pStartup;
}
void freeStruct1(struct FOUNDERS * pFounder){
    free(pFounder);
}
void freeStruct2(struct STARTUP * pStartup){
    free(pStartup);
}

void printElStruct1(int size, struct FOUNDERS founder[size]){
    int i;
    for(i = 0; i < size; i++){
        printStruct1(&founder[i]);
    }
}
void printElStruct2(int size, struct STARTUP startup[size]){
    int i;
    for(i = 0; i < size; i++){
        printStruct2(&startup[i]);
    }

}

void fillStruct1(struct FOUNDERS * pFounder){
    struct tm * pTime = (struct tm *)malloc(sizeof(struct tm));
    int year;
    int month;
    int day;
    printf("Enter name of founder of startup: ");
    gets(pFounder->nameFounder);
    printf("Enter date of birth.");
    printf("Year:");
    pTime->tm_year = scanf("%i", &year) - 1900;
    printf("Month:");
    pTime->tm_mon = scanf("%i", &month) - 1;
    printf("Day:");
    pTime->tm_mday = scanf("%i", &day);
    pFounder->ageFounder = mktime(pTime);
}

void fillStruct2(struct STARTUP * pStartup){
    int invest;
    printf("Enter name of founder of startup: ");
    gets(pStartup->nameFounder);
    printf("Enter name of startup:");
    gets(pStartup->nameStartUp);
    printf("Enter investments:");
    scanf("%i", &invest);
}




