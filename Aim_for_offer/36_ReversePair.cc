#include <stdio.h>

int Merge(int* numbers,int left,int right,int* copy)
{
	if (left == right) return 0;
	int center = (left + right) >> 1;
	int Left = Merge(numbers,left,center,copy);
	int Right = Merge(numbers,center + 1,right,copy);
	int count = 0;

	int LeftIndex = center;
	int RightIndex = right;
	int CopyIndex = right;
	while (LeftIndex >= left && RightIndex >= center + 1)
	{
		if (numbers[LeftIndex] > numbers[RightIndex])
		{
			count += RightIndex - center;
			copy[CopyIndex--] = numbers[LeftIndex--];
		}
		else
		{
			copy[CopyIndex--] = numbers[RightIndex--];
		}
	}
	while (LeftIndex >= left)
		copy[CopyIndex--] = numbers[LeftIndex--];
	while (RightIndex >= center + 1)
		copy[CopyIndex--] = numbers[RightIndex--];
	for (int i = left;i <= right;++i)
		numbers[i] = copy[i];
	return Left + Right + count;
}

int ReversePair(int* numbers,int length)
{
	if (numbers == NULL || length <= 0)
		return -1;
	int copy[length];
	return Merge(numbers,0,length - 1,copy);
}

int main()
{
	int test[] = {7,5,6,4};
	printf("%d\n",ReversePair(test,3));
}
