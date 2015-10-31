#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randomArr(int A[], int B[], int C[]);
void printArr(int A[], int B[], int C[]);

int main()
{
   int A[200];
   int B[200];
   int C[200];
   srand(time(NULL));
   randomArr(A,B,C);
   printArr(A,B,C);
}

