#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double calc(double x, double y, double z)
{
    double a,a0,a1,a2;

    a0=pow(x,y+1)/pow(x-y,1/z);
    a1=6*y +z/x;
    a2=pow(x,1/abs(sin(y)));
    a=a0+a1+a2;

   if((x==y)||(z==0)||(x==0)||(sin(y)==0)){
        return NAN;
    } else {
    return a;
    }
}
