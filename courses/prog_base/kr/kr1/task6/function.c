#include<stdio.h>
#include<stdlib.h>

void randomArr(int A[], int B[], int C[])
{
int i,j,k;
for(i=0,j=0,k=0;i<200,j<200,k<200; i++,j++,k++){
    A[i]= rand()%200;
    B[i]= rand()%200;
    C[i]= rand()%200;
}
}

void printArr(int A[], int B[], int C[])
{
    int i,j,k;
    for(i=0; i<200; i++){
        switch(i){
     case 0 ... 3:
        printf("%i", A[i]);
        break;
    case 5:
        printf("%i", A[i]);
        break;
    case 7:
        printf("%i", A[i]);
        break;
    case 9 ... 123:
        printf("%i", A[i]);
        break;
    case 156:
        printf("%i", A[i]);
        break;
    case 158:
        printf("%i", A[i]);
        break;
    }
}
}


