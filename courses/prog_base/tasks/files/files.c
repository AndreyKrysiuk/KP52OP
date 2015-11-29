#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void fprocess(const char * pread, const char * pwrite){
    FILE * fp1;
    FILE * fp2;
    int count;
    int size;
    int countsymbols = 0;
    int i;
    char str[999];
    char * sp;

    fp1 = fopen(pread, "r");
    fp2 = fopen(pwrite, "w");

    if (NULL == fp1) {
        exit(EXIT_FAILURE);
    }
    if (NULL == fp2) {
        exit(EXIT_FAILURE);
    }

    for(count = 1; count < 7; count++){
    fgets(str, 999, fp1);
    }
    size = strlen(str);
	sp = strtok(str, " ");
	while(sp){
        sp = strtok(NULL, " ");
	}
	for(i = 0; i < size; i++){
        if(isalnum(str[i])!=0){
            countsymbols++;
        }
	}


    fprintf(fp2, "%i", countsymbols);

    fclose(fp1);
    fclose(fp2);
}

