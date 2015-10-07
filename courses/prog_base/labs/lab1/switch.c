#include<math.h>
int exec(int op, int a, int b)
{
    int result;
    int data_type;
    double pi = 3.14;
    if (op<0){
    int c;
    c = a;
    a = b;
    b = c;
    }
    switch (abs(op)){
    case 0:
        result = -a;
        break;
    case 1:
        result = a+b;
        break;
    case 2:
        result = a-b;
        break;
    case 3:
        result = a*b;
        break;
    case 4:
        result = a/b;
        break;
    case 5:
        result = abs (a);
        break;
    case 6:
        result = pow(a,b);
        break;
    case 7:
    case 13:
    case 77:
        result = a%b;
        break;
    case 8:
        result = fmax(a,b);
        break;
    case 9:
        result = fmin(a,b);
        break;
    case 10:
        data_type = abs(b)%8;
        switch(data_type){
        case 0:
            result = abs(a)*sizeof(char);
            break;
        case 1:
            result = abs(a)*sizeof(signed char);
            break;
        case 2:
            result = abs(a)*sizeof(short);
            break;
        case 3:
            result = abs(a)*sizeof(unsigned int);
            break;
        case 4:
            result = abs(a)*sizeof(long);
            break;
        case 5:
            result = abs(a)*sizeof(unsigned long long);
            break;
        case 6:
            result = abs(a)*sizeof(float);
            break;
        case 7:
            result = abs(a)*sizeof(double);
            break;
        }
        case 11:
            result = pow(a,(6+b))/pi;
        default:
            if (op<100) {
                result = (op%abs(a+1))+(op%abs(b+1));
                break;
            } else {
            result = -1;
            }
    }
return result;
}
