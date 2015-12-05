#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

struct Photograph {
    int photoNum;
    time_t photoDate;
    char description[50];
    };

int count(int size, struct Photograph arr[size]){
    int countPhoto = 0;
    int i;
    for(i = 0; i < size; i++){
        if(difftime(time(NULL),arr[i].photoDate) < (30*24*60*60)){
        } else {
        countPhoto++;}
    }
    return countPhoto;
}

void change(struct Photograph * pVar, const char * newValue){
    strcpy(pVar->description, newValue);
}

void print(struct Photograph * pVar){
printf("Description: %s\n", pVar->description);
printf("Date foto: %s", ctime(&(pVar->photoDate)));
printf("Number of foto: %i\n", pVar->photoNum);
}

int main()
{
    int i;
    char newstr[100];

    struct Photograph Photo[5];

    int size = sizeof(Photo)/sizeof(Photo[0]);

    struct tm * pTime = (struct tm *)malloc(sizeof(struct tm));
    if (NULL == pTime) {
        return 1;
    }
    for(i = 0; i < size; i++){
    pTime->tm_mday = ((rand()%31));
    pTime->tm_mon  = ((rand()%12));
    pTime->tm_year = ((rand()%5) + 111);
    pTime->tm_hour = ((rand()%24));
    pTime->tm_min  = ((rand()%60));
    pTime->tm_sec  = ((rand()%60)  + 1);
    Photo[i].photoDate = mktime(pTime);
    strcpy(Photo[i].description, "TDG concert 29/01/16");
    Photo[i].photoNum = i;
    print(&(Photo[i]));
    }
    printf("\nCountPhoto: %i\n", count(size, Photo));


    printf("Please, enter new description\n");
    gets(newstr);
    printf("Please, enter number of photo: ");
    scanf("%i", &i);
    change(&Photo[i], newstr);
    print(&(Photo[i]));

    return 0;
}
