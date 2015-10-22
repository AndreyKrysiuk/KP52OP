#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void fillRand(int mat[4][4])
{
    int i,j;
    srand(time(NULL));
    for(i = 0; i<4; i++){
        for( j=0; j<4; j++){
            mat[i][j] = pow(-1,rand())*(rand()%1000);
        }
    }
}



void rotateCW90(int mat[4][4])
{
int i,j;
int tmp;
for(i=0; i<2; i++)
    {
    for(j=i; j<3-i; j++)
        {
        tmp = mat[i][j];
        mat[i][j] = mat[3-j][i];
        mat[3-j][i] = mat[3-i][3-j];
        mat[3-i][3-j] = mat[j][3-i];
        mat[j][3-i] = tmp;
        }
    }
}





void flipH(int mat[4][4])
{
int i,j, tmp;
for(i=0; i<4; i++)
    {
        for(j=0; j<2; j++)
        {
        tmp = mat[i][j];
        mat[i][j] = mat[i][3-j];
        mat[i][3-j] = tmp;
        }
    }
}




void transposMain(int mat[4][4])
{
int i,j, tmp;
for(i=0; i<4; i++)
    {
    for(j=0; j<i; j++)
        {
        tmp = mat[i][j];
        mat[i][j] = mat[j][i];
        mat[j][i] = tmp;
        }
    }
}
