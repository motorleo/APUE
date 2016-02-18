#include <stdio.h>

bool CheckMoreThanHalf(int* numbers,int length,int number)
{
	int times;
	for (int i = 0;i < length;++i)
	{
		if (numbers[i] == number) ++times;
	}
	if (times*2 > length) return true;
	else return false;
}

void MoreThanHalfNumber(int* numbers,int length)
{
	if (numbers == NULL || length <= 0) return;
	int num = 0;
	int times = 0;
	for (int i = 0;i < length;++i)
	{
		if (times == 0)
		{
			num = numbers[i];
			++times;
		}
		else if (num == numbers[i])
		{
			++times;
		}
		else
		{
			--times;
		}
	}
	if (times == 0 || !CheckMoreThanHalf(numbers,length,num))
	{
		printf("invalid input!\n");
	}
	else 
	{
		printf("%d\n",num);
	}
}

int main()
{
	int test[] = {1,2,3,2,2,5,4,2,2};
	MoreThanHalfNumber(test,9);
}
