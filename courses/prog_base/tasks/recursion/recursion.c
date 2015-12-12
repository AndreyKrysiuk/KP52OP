#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int countXdigits(char * str);

int main()
{
    char string[160];
    fflush(stdin);
    fgets(string, 160, stdin);
    fclose(stdin);
    printf("%d", countXdigits(string));
    return 0;
}


int countXdigits(char * str){
    int count = 0;
    if(*str != '\0'){
        if(isxdigit(*str) != 0){
            count++;
        }
        return count + countXdigits(str + 1);
    } else {
    return count;
    }
}
