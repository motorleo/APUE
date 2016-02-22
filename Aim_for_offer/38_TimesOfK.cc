#include <stdio.h>

int GetFirstK(int* numbers,int left,int right,int k)
{
	if (left > right) return -1;
	int center = (left + right) >> 1;
	if (numbers[center] == k)
	{
		if ((center > 0 && numbers[center - 1] != k) || center == 0)
			return center;
		else
			return GetFirstK(numbers,left,center - 1,k);
	}
	if (numbers[center] < k)
		return GetFirstK(numbers,center + 1,right,k);
	if (numbers[center] > k)
		return GetFirstK(numbers,left,center - 1,k);
}

int GetLastK(int* numbers,int length,int left,int right,int k)
{
	if (left > right) return -1;
	int center = (left + right) >> 1;
	if (numbers[center] == k)
	{
		if ((center < length - 1 && numbers[center + 1] != k) 
				|| center == length - 1)
			return center;
		else
			return GetLastK(numbers,length,center + 1,right,k);
	}
	if (numbers[center] < k)
		return GetLastK(numbers,length,center + 1,right,k);
	if (numbers[center] > k)
		return GetLastK(numbers,length,left,center - 1,k);
	
}

int TimesOfK(int* numbers,int length,int k)
{
	if (numbers == NULL || length <= 0) return -1;
	int left = GetFirstK(numbers,0,length - 1,k);
	printf("%d\n",left);
	if (left == -1) return 0;
	int right = GetLastK(numbers,length,0,length - 1,k);
	printf("%d\n",right);
	return right - left + 1;
}


int main()
{
	int test[] = {1,2,3,3,3,3,4,5};
	printf("%d\n",TimesOfK(test,3,3));
}
