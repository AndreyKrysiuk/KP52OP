#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
//variant n 16 n1
void sum(const char * pread, const char * pwrite);

int main()
{

    const char * filename1  = "input.txt";
    const char * filename2  = "output.txt";
    sum(filename1, filename2);
      return 0;
}

void sum(const char * pread, const char * pwrite){
    FILE * fp1;
    FILE * fp2;
    int count;
    double sum = 0;
    double num = 0;
    fp1 = fopen(pread, "r");
    fp2 = fopen(pwrite, "w");
    if (NULL == fp1) {
        exit(EXIT_FAILURE);
    }
    if (NULL == fp2) {
        exit(EXIT_FAILURE);
    }
    char start1[800];
    char *end, *start;
    for(count = 1; count < 4; count++) {
        start = fgets(start1, 200, fp1);
        while(*start) {
            if(strtod(start, &end) > 3.0){
            sum += strtod(start, &end);
            }
            start = end;
            while(!isdigit(*start) && *start) start++;
        }
        fprintf(fp2, "Sum of string %i: %f\n", count, sum);
      }
    fclose(fp1);
    fclose(fp2);
}
