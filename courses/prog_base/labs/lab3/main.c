#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include"main.h"
#include<float.h>


int main(){

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int fmt;

    int size;
    char cmd[80];
    int i,k,j;
    int exitcheck = 0;
    int scanfcheck = 0;
    double value;
    double range1, range2;
    printf("Please, enter size of matrix (from 2 to 7) >> ");
    while((scanfcheck != 1)||(size <= 1)||(size > 7)){
        fflush(stdin);
        scanfcheck = scanf("%i", &size);
        if((scanfcheck != 1)||(size <= 1)||(size > 7)){
            printf("Invalid size of matrix, please, re-enter >> ");
        }
    }
    scanfcheck = 0;
    system("cls");
    printWorkZone(size);
    double matrix[size][size];
    nullMatrix(size, matrix);
    while(exitcheck != 1){
        printMatrix(size, matrix);
        scanprint(size);
        fmt = 0x00A;
        SetConsoleTextAttribute(hConsole, fmt);
        scanf("%s", &cmd);
        fmt = 0x00F;
        SetConsoleTextAttribute(hConsole, fmt);
        system("cls");
        printWorkZone(size);
        if(strcmp(cmd, "null")== 0){
            nullMatrix(size, matrix);
            printMatrix(size, matrix);
            } else if(strcmp(cmd, "fill")==0) {
                printMatrix(size, matrix);
                printf("Please, enter first end of the range [min: -99999, max: 99999] >> ");
                while((scanfcheck != 1)||(range1 < -99999)||(range1 > 99999)){
                    fflush(stdin);
                    scanfcheck = scanf("%lf", &range1);
                    if((scanfcheck != 1)||(range1 < -99999)||(range1 > 99999)){
                        printf("Invalid range, please, re-enter >> ");
                    }
                }
                scanfcheck = 0;
                printf("Please, enter second end of the range [min: -99999, max: 99999] >> ");
                while((scanfcheck != 1)||(range2 < -99999)||(range2 > 99999)){
                    fflush(stdin);
                    scanfcheck = scanf("%lf", &range2);
                    if((scanfcheck != 1)||(range2 < -99999)||(range2 > 99999)){
                        printf("Invalid range, please, re-enter >> ");
                    }
                }
                scanfcheck = 0;
                srand(time(NULL));
                fillMatrix(size, matrix, range1, range2);
                system("cls");
                printWorkZone(size);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "change")==0) {
                printMatrix(size, matrix);
                printf("Please, enter number of row [from 0 to %i] >> ", size-1);
                while((scanfcheck != 1)||(i < 0)||(i >= size)){
                    fflush(stdin);
                    scanfcheck = scanf("%i", &i);
                    if((scanfcheck != 1)||(i < 0)||(i >= size)){
                        printf("Invalid number, please, re-enter >> ");
                    }
                }
                scanfcheck = 0;
                printf("Please, enter number of column [from 0 to %i] >> ", size-1);
                while((scanfcheck != 1)||(k < 0)||(k >= size)){
                    fflush(stdin);
                    scanfcheck = scanf("%i", &k);
                    if((scanfcheck != 1)||(k < 0)||(k >= size)){
                        printf("Invalid number, please, re-enter >> ");
                    }
                }
                scanfcheck = 0;
                printf("Please, enter new value [from -99999 to 99999 >> ");
                while((scanfcheck != 1)||(value < -99999)||(value > 99999)){
                    fflush(stdin);
                    scanfcheck = scanf("%lf", &value);
                    if((scanfcheck != 1)||(value < -99999)||(value > 99999)){
                        printf("Invalid value, please, re-enter >> ");
                    }
                }
                scanfcheck = 0;
                matrix[i][k] = value;
                system("cls");
                printWorkZone(size);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "flip")==0){
                flipV(size, matrix);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "trans")==0){
                transposMain(size, matrix);
                printMatrix(size, matrix);
            } else if((strcmp(cmd, "rotate")==0)){
                rotateCW90(size, matrix);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "summat")==0){
                setCursor(size);
                printf("Sum of elements matrix: %.2f\n", sumElements(size, matrix));
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "sumrow")==0){
                printMatrix(size, matrix);
                printf("Please, enter number of row [from 0 to %i] >> ", size-1);
                while((scanfcheck != 1)||(j < 0)||(j >= size)){
                    fflush(stdin);
                    scanfcheck = scanf("%i", &j);
                    if((scanfcheck != 1)||(j < 0)||(j >= size)){
                        printf("Invalid number, please, re-enter >> ");
                    }
                }
                scanfcheck = 0;
                system("cls");
                printWorkZone(size);
                setCursor(size);
                printf("Sum of elements row %i: %.2f\n", j, sumString(j,size, matrix));
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "sumdg")==0){
                setCursor(size);
                printf("Sum of elements above main diagonal: %.2f\n", sumDiagonal(size, matrix));
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "first")==0){
                firstMinToMax(size, matrix);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "last")==0){
                lastMinToMax(size, matrix);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "move")==0){
                moveTwoStrings(size, matrix);
                printMatrix(size, matrix);
            } else if(strcmp(cmd, "help")==0){
                printf("Help:\n");
                printf("All commands are case sensitive.\n"
                        " null   - set all elements to zero;\n"
                        " fill   - fill a matrix with random numbers in selected range;\n"
                        " change - change selected element to user value;\n"
                        " flip   - flip matrix vertically;\n"
                        " trans  - rotation about the main diagonal;\n"
                        " rotate - rotate 90 degrees clockwise;\n"
                        " summat - sum of matrix elements;\n"
                        " sumrow - sum of elements of selected row;\n"
                        " sumdg  - sum of elements above main diagonal;\n"
                        " first  - change places of first minimal and first maximal element;\n"
                        " last   - change places of last minimal and first maximal element;\n"
                        " move   - change places of strings with min and max sum of element;\n"
                        " exit   - exit from the program;\n");
            } else if(strcmp(cmd, "exit")==0){
                exitcheck = 1;
            } else {
                printf("Invalid command, please, re-enter\n");
        }
    }
    return 0;
}

