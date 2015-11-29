#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>

void fillMatrix(int size, double arr[size][size], double range1, double range2){
    int i,k;
    double max_range = fmax(range1, range2);
    double min_range = fmin(range1, range2);
     for(i = 0; i < size; i++){
        for(k = 0; k < size; k++){
            arr[i][k] = (float) rand()/RAND_MAX*(max_range-min_range) + min_range;
        }
    }
}

void nullMatrix(int size, double arr[size][size]){
    int i,k;
    for(i = 0; i < size; i++){
        for(k = 0; k < size; k++){
            arr[i][k] = 0;
        }
    }
}

void printMatrix(int size, double arr[size][size])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int fmt;
    fmt = 0x0F0;
    SetConsoleTextAttribute(hConsole, fmt);
    int i, k;
    for(i = 0; i < size; i++){
            pos.X = 2;
            pos.Y = 3 + i;
            SetConsoleCursorPosition(hConsole, pos);
            printf("{ ");
        for(k = 0; k < size; k++){
            printf("%7.2f  ", arr[i][k]);
        }
        printf("}\n");
    }

    pos.X = 0;
    pos.Y = size + 7;
    SetConsoleCursorPosition(hConsole, pos);
    fmt = 0x00F;
    SetConsoleTextAttribute(hConsole, fmt);
}

void rotateCW90(int size, double arr[size][size])
{
int i,k;
double tmp;
    for (i = 0; i < size / 2; ++i)
    {
      for (k = i; k < size - i - 1;++k)
      {
        tmp = arr[i][k];
        arr[i][k] = arr[size-k-1][i];
        arr[size-k-1][i] = arr[size-i-1][size-k-1];
        arr[size-i-1][size-k-1] = arr[k][size-i-1];
        arr[k][size-i-1] = tmp;
      }
    }
}

void transposMain(int size, double mat[size][size])
{
int i,j;
double tmp;
for(i=0; i<size; i++)
    {
    for(j=0; j<i; j++)
        {
        tmp = mat[i][j];
        mat[i][j] = mat[j][i];
        mat[j][i] = tmp;
        }
    }
}

double sumElements(int size, double mat[size][size])
{
    int i,j;
    double sum = 0;

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            sum += mat[i][j];
        }
    }
    return sum;
}

double sumString(int i, int size, double mat[size][size])
{
    int j;
    double sum = 0;

    for(j = 0; j < size; j++){
        sum += mat[i][j];
    }
    return sum;
}

double sumDiagonal(int size, double mat[size][size])
{
    int i,j,k;
    double sum = 0;
    for(i = 0, k = 0; i < size, k < size; i++, k++){
        for ( j = k; j < size; j++){
                sum += mat[i][j];
        }
    }
    return sum;
}

void moveTwoStrings(int size, double mat[size][size])
{
    int i,j;
    double tmp;
    int indexMax = 0;
    int indexMin = 0;
    double sum = 0;
    double sumMax = -sumElements(size, mat);
    double sumMin = sumElements(size, mat);

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            sum += mat[i][j];
            }
            if(sum > sumMax){
                sumMax = sum;
                indexMax = i;
            }
            if(sum < sumMin){
                sumMin = sum;
                indexMin = i;
        }
    }
    for(j = 0; j < size; j++){
        tmp = mat[indexMin][j];
        mat[indexMin][j] = mat[indexMax][j];
        mat[indexMax][j] = tmp;
    }
}

void flipV(int size, double mat[size][size])
{
int i,j;
double tmp;
for(i = 0; i < size / 2; i++)
    {
        for(j = 0; j < size; j++)
        {
        tmp = mat[i][j];
        mat[i][j] = mat[size - 1 - i][j];
        mat[size - 1 - i][j] = tmp;
        }
    }
}

void firstMinToMax(int size, double mat[size][size])
{
    int i,j;
    double tmp;
    int maxI = 0, maxJ = 0, minI = 0, minJ = 0;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(mat[i][j] < mat[minI][minJ]){
                minI = i;
                minJ = j;
            }
            if(mat[i][j] > mat[maxI][maxJ]){
                maxI = i;
                maxJ = j;
            }
        }
    }
    tmp = mat[minI][minJ];
    mat[minI][minJ] = mat[maxI][maxJ];
    mat[maxI][maxJ] = tmp;
}

void lastMinToMax(int size, double mat[size][size])
{
    int i,j;
    double tmp;
    int maxI = 0, maxJ = 0, minI = 0, minJ = 0;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(mat[i][j] <= mat[minI][minJ]){
                minI = i;
                minJ = j;
            }
            if(mat[i][j] > mat[maxI][maxJ]){
                maxI = i;
                maxJ = j;
            }
        }
    }
    tmp = mat[minI][minJ];
    mat[minI][minJ] = mat[maxI][maxJ];
    mat[maxI][maxJ] = tmp;
}

void scanprint(int size){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = 0;
    pos.Y = size + 6;
    SetConsoleCursorPosition(hConsole, pos);
    printf("Please, enter command (enter 'help' to open help): ");
}

void printWorkZone(int n){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int fmt;
    fmt = 0x0F0;
    SetConsoleTextAttribute(hConsole, fmt);
    for(pos.Y = 0; pos.Y < n + 6; pos.Y++){
        for(pos.X = 0; pos.X < 80; pos.X++){
            if((pos.Y == 0)||(pos.Y == n + 5)) {
                SetConsoleCursorPosition(hConsole, pos);
                printf("=");
            } else {
            SetConsoleCursorPosition(hConsole, pos);
            printf(" ");
            }
        }
    }
    pos.X = 0;
    pos.Y = n + 7;
    SetConsoleCursorPosition(hConsole, pos);
    fmt = 0x00F;
    SetConsoleTextAttribute(hConsole, fmt);
}

void setCursor(int size)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    int fmt;
    fmt = 0x0F0;
    pos.X = 4;
    pos.Y = size + 4;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, fmt);
}
