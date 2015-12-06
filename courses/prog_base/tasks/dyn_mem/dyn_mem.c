#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){
    char *p = NULL;
    p = malloc(400 * sizeof(char));
    fgets(p, 400, stdin);

    int *i = malloc(sizeof(int));
    int *count = malloc(sizeof(int));
    *count=0;
    int *lastxDec = malloc(sizeof(int));

    for(*(i) = 0; *(i) < strlen(p)-1; *(i)+=1){
        if(isxdigit(p[*i]) != 0){
            *lastxDec = *i;
            *(count)+=1;
        }
    }

    if(*count != 0){
        printf("Last symbol of hexadecimal number is %c", p[*lastxDec]);
    } else {
    printf("0");
    }

    free(lastxDec);
    free(i);
    free(count);
    free(p);
    return 0;
}



