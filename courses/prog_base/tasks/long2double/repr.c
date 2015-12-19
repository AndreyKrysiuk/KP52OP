#include<math.h>

double long2double(long long num){
    unsigned long long mask = 1;
	mask <<= 63;
	int count = 0;
	int sign = 0;
	short int e = 0;
	double m = 0;
	if (mask == (num&mask))
		sign = 1;
	mask >>= 1;
	count++;
	int powN = 10;
	for (count; count < 12; count++)
	{
		if (mask == (num&mask))
			e += pow(2, powN);
		powN--;
		mask >>= 1;
	}
	for (count; count < 64; count++)
	{
		if (mask == (num&mask))
			m += pow(2, powN);
		powN--;
		mask >>= 1;
	}
	if (e == 2047 && m > 0)
		return pow(-1, sign)*NAN;
	else if (e == 2047)
		return pow(-1, sign)*INFINITY;
	else if (e == 0 && m == 0)
		return pow(-1, sign)*0.0;
	else if (e == 0 && m > 0)
		return pow(-1, sign)*pow(2,-1022) * (m);
	else if(e > 0 && e < 2047)
		return pow(-1, sign)*pow(2, e - 1023) * (1 + m);
}

