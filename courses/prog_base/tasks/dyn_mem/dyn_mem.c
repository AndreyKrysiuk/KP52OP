#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    char *p = NULL;
    p = malloc(400 * sizeof(char));
    fgets(p, 400, stdin);

    char *i;
    int *count = 0;
    char *lastxDec = malloc(sizeof(char));

    for(i = p; *i != '\n'; i++){
        if(isxdigit(*i) != 0){
            lastxDec = i;
            count++;
        }
    }

    if(count != 0){
        printf("Last symbol of hexadecimal number is %c", *lastxDec);
    } else {
    printf("0");
    }

    free(lastxDec);
    free(p);
    return 0;
}


