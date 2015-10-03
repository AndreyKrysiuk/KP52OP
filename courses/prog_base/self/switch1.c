#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
int h = 2;
int n = 15;
int code;
scanf("%d", &code);
float price;
if (code>=10&&code<=999){
switch (code){
case 44:
price = (h*60 + n)*0.77;
printf("%f\n",price);
break;
case 62:
price = (h*60 + n)*0.8;
printf("%f\n",price);
break;
case 32:
price = (h*60 + n)*0.95;
printf("%f\n",price);
break;
case 692:
price = (h*60 + n)*1.5;
printf("%f\n",price);
break;
case 697:
price = (h*60 + n)*1.5;
printf("%f\n",price);
break;
default:
price = (h*60 + n)*1;
printf("%f\n",price);
break;
}
return 0;
}
}
