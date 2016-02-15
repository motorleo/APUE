#include <stdio.h>
#include <string.h>

bool Increment(char* number,int numberLength)
{
	bool overflow = false;
	if (number[numberLength - 1] != '9')
	{
		++number[numberLength - 1];
	}
	else
	{
		int index = numberLength - 2;
		while (index >= 0 && number[index] == '9') --index;
		if (index == -1) 
		{
			overflow = true;
		}
		else
		{
			++number[index];
			memset(number+(index+1),'0',numberLength-index-1);
		}
	}
	return overflow;
}

void PrintNumber(char* number)
{
	char* startPrint = number;
	while (*startPrint == '0') ++startPrint;
	printf("%s\n",startPrint);
}

void PrintNOfMaxNumber(int n)
{
	if (n <= 0) return;
	char number[n+1];
	memset(number,'0',n);
	number[n] = '\0';
	while (!Increment(number,n))
		PrintNumber(number);
}

int main()
{
	PrintNOfMaxNumber(-1);
	PrintNOfMaxNumber(0);
	PrintNOfMaxNumber(3);
	return 0;
}
