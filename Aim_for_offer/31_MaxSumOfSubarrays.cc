#include <stdio.h>

int MaxSum(int* numbers,int length)
{
	if (numbers == NULL || length <= 0) return 0;
	int sum = 0;
	int maxsum = 0;
	for (int i = 0;i < length;++i)
	{
		sum += numbers[i];
		if (sum < 0) 
			sum = 0;
		else 
			maxsum = sum > maxsum ? sum:maxsum;
	}
	return maxsum;
}

int main()
{
	int test[] = {1,-2,3,10,-4,7,2,-5};
	printf("%d \n",MaxSum(test,1));
}
