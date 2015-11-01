#include <string.h>
#include <stdio.h>

char * process(char * resultStr, const char * textLines[],
               int linesNum, const char * extraStr) {
    int i, j, k, check;
    int extraLineNum;
    const char * line;
    char extraStrTrans[100];
    for(i = 0; i < linesNum; i++)
        {
        line = textLines[i];

        }
    for(i = strlen(extraStr)-1, j=0; i >=0;j++, i--)
    {
        extraStrTrans[j]=extraStr[i];
    }
    extraStrTrans[j] = '\0';
    for(i = 0; i < linesNum; i++){
           check = strcmp(textLines[i], extraStrTrans);
            if( check == 0){
                extraLineNum  = i;
                break;
            }

    }
    if( check == 0){
    sprintf(resultStr, "This is result: %i %s", extraLineNum, extraStrTrans);
    } else {
    sprintf(resultStr, "This is result: 0 NULL %s", extraStr);
    }
    return resultStr;
}
