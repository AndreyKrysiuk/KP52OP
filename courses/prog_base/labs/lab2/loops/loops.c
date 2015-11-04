#include<stdio.h>
#include<math.h>

double calc(int n, int m){
    int i, j;
    double x = 0;
    double result = 0;
    for(i=1; i<=n; i++){
        for(j=1; j<=m; j++){
            x += (pow(i,2) + (10/(double)j));
        }
    result+=x;
    x = 0;

}
return result;
}

