#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct String{
    char symbol;
    int pos;
};

void saveSymbol(char * str, struct String String1[80]){
    int i = 0;
        for(i = 0; i < strlen(str); i++){
            if(isdigit(str[i])==1){
                String1[i].symbol = str[i];
                String1[i].pos = i;
                printf("Symbol: %c\n", String1[i].symbol);
                printf("Position: %i\n", String1[i].pos);
            }
        }
        printf("Len of massive: %i", strlen(str));
}

int main()
{
    printf("Please, enter string:");
    char str[80];
    gets(str);
    struct String String1[80];

    saveSymbol(str, String1);
    return 0;
}


