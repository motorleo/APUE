#include <stdio.h>

void TwoSum(int* numbers,int length,int s)
{
	if (numbers == NULL || length <= 1) return;
	int left = 0;
	int right = length - 1;
	while (left < right)
	{
		if (numbers[left] + numbers[right] == s)
		{
			printf("%d %d\n",numbers[left],numbers[right]);
			break;
		}
		else if (numbers[left] + numbers[right] < s)
		{
			++left;
		}
		else
		{
			--right;
		}
	}
}

int SumOfSequence(int left,int right)
{
	int length = right - left + 1;
	int result = length * (left + right) >> 1;
	return result;
}

void SequenceWithSum(int s)
{
	if (s < 3) return;
	int small = 1;
	int big = 2;
	int center = s >> 1;
	int sum = 0;
	while (small <= center && small < big)
	{
		sum = SumOfSequence(small,big);
		if (sum == s)
		{
			for (int i = small;i <= big;++i)
				printf("%d ",i);
			printf("\n");
			++small;
		}
		else if (sum < s)
		{
			++big;
		}
		else
		{
			++small;
		}
	}
}

int main()
{
	SequenceWithSum(15);
}
