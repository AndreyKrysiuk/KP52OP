#include<math.h>

double long2double(long long n){
	int i;
	int charn;
	int exp, E = 0, sign;
	double F = 0;
	double result = 0;
	char binary[64] = "";
	long long n1;
	for (charn = 63; charn >= 0; charn--)
    {
		n1 = n;
		n1 = n1 >> 1;
		n1 = n1 << 1;
		if (n==n1)
            {
            binary[charn]='0';
            } else {
                binary[charn]='1';
            }
		n = n >> 1;
	}
	for (charn = 12, exp = -1; charn <= 63; charn++, exp--)
	{
		if (binary[charn] == '1')
            {
			F= F + pow(2, exp);
            }
	}
	for (charn = 11, exp = 0; charn >= 1; charn--, exp++)
        {
		if (binary[charn] == '1')
		{
			E = E + pow(2, exp);
		}
	}
	if ((E == 0) && (F != 0))
        {
		result = (1+F)*pow(2, -1022);
            if(sign == -1)
            {
                result = -result;
            }
		}

	else {
		result = (1+F)*pow(2, E - 1023);
            if(sign == -1)
                {
                result = -result;
                }
        }

	if ((E == 2047) && (F!= 0) && (binary[0] == '0'))
        {
        return NAN;
        }

	return result;
}
