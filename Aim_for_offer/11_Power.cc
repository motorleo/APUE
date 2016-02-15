#include <stdio.h>
#include <stdlib.h>

bool equal(double lhs,double rhs)
{
	double temp = lhs - rhs;
	if (0.0000001 > temp && temp > -0.0000001)
		return true;
	return false;
}

double PowerWithUnsigned(double base,unsigned exponent)
{
	if (exponent == 0) return 1.0;
	if (exponent == 1) return base;
	double result = PowerWithUnsigned(base,exponent >> 1);
	result *= result;
	if (exponent & 1) result *= base;
	return result;
}

double Power(double base,int exponent)
{
	if (equal(base,0.0)) return 0.0;
	double result = PowerWithUnsigned(base,abs(exponent));
	if (exponent < 0) result = 1/result;
	return result;
}

int main()
{
	printf("2,2:%lf\n",Power(2.0,2));
	printf("2,-2:%lf\n",Power(2.0,-2));
	printf("2,0:%lf\n",Power(2.0,0));
	printf("0,2:%lf\n",Power(0.0,2));
	printf("0,-2:%lf\n",Power(0.0,-2));
	printf("0,0:%lf\n",Power(0.0,0));
	printf("-2,2:%lf\n",Power(-2.0,2));
	printf("-2,-2:%lf\n",Power(-2.0,-2));
	printf("-2,0:%lf\n",Power(-2.0,0));
}
