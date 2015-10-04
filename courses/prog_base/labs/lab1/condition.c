#include<math.h>

int satisfies(int a,int b, int c){
    int result;
    if (a<0&&b<0&&c<0)
    {
        int modmin;
        int sum2;
        int n;
        modmin = fmin(fmin(abs(a),abs(b)),abs(c));
        sum2 = a+b+c-fmax(fmax(a,b),c);
        if ((sum2<-256&&(modmin=pow(2,n))&&
             n>=0&&(modmin<256))){
                 result=1;
                 } else {
                     if(sum2>modmin&&sum2>-256){
                            result=1;
                     } else {
                         result=0;}
                     }
    }
    else {
        if ((a<0&&b>=0&&c>=0&&a>-256)||
            (a>=0&&b<0&&c>=0&&b>-256)||
            (a>=0&&b>=0&&c<0&&c>-256)){
                result = 1;
                } else {
                        if ((a<0&&b<0&&c>=0&&((a+b)*6>-256))||
                            (a<0&&b>=0&&c<0&&((a+c)*6>-256))||
                            (a>=0&&b<0&&c<0&&((b+c)*6>-256))){
                            result = 1;
                        } else {
                                if(a>0&&b>0&&c>0){
                                int max;
                                int min;
                                max=fmax(fmax(a,b),c);
                                min=fmin(fmin(a,b),c);
                                    if(max+min<256){
                                    result=1;
                                } else {
                    result=0;}
        } else {
            result=0;}

            }
        }
        return result;
    }
}
