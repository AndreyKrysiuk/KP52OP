#include <string.h>
#include <stdio.h>

char * process(char * resultStr, const char * textLines[], int linesNum, const char * extraStr){
    int check;
    int extraLineNum;
    int k = 0;
    int i;
    char extraStrInverse[100] = "\0";

    for (i = strlen(extraStr)-1; i >= 0; i--){
        extraStrInverse[k++] = extraStr[i];
    }

    for(i = 0; i < linesNum; i++){
           check = strcmp(textLines[i], extraStrInverse);
            if( check == 0){
                extraLineNum  = i;
                sprintf(resultStr, "This is result: %i %s", extraLineNum, extraStrInverse);
                break;
            } else {
                sprintf(resultStr, "This is result: 0 NULL %s", extraStrInverse);
            }
    }
    return resultStr;
}
