#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>

int TimesOf1(char* Nstr,int length)
{
	if (length <= 0) return 0;
	int result = 0;
	int base = 1;
	//highest digit
	if (Nstr[0] == '0')
	{
		return TimesOf1(Nstr + 1,length - 1);
	}
	else if (Nstr[0] == '1')
	{
		result = atoi(Nstr + 1) + 1;
	}
	else
	{
		for (int i = 1;i < length;++i)
			base *= 10;
		result = base;
	}
	//rest digits
	int highestDigit = Nstr[0] - '0';
	base = 1;
	for (int i = 2;i < length;++i)
		base *= 10;
	result += base * highestDigit * (length - 1);
	//next loop
	result += TimesOf1(Nstr + 1,length - 1);
	return result;
}

int TimesOf1(int n)
{
	if (n <= 0) return 0;
	char Nstr[50];
	sprintf(Nstr,"%d",n);
	return TimesOf1(Nstr,strlen(Nstr));
}

int main()
{
	printf("%d\n",TimesOf1(1));
}
