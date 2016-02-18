#include <stdio.h>
#include <algorithm>

using std::swap;
int Median3(int* numbers,int left,int right)
{
	int center = (left + right) >> 1;
	if (numbers[left] > numbers[center])
		swap(numbers[left],numbers[center]);
	if (numbers[left] > numbers[right])
		swap(numbers[left],numbers[right]);
	if (numbers[center] > numbers[right])
		swap(numbers[center],numbers[right]);
	swap(numbers[center],numbers[right - 1]);
	return numbers[right - 1];
}

void printKNumbers(int* numbers,int k)
{
	for (int i = 0;i < k;++i)
	{
		printf("%d ",numbers[i]);
	}
	printf("\n");
}

void InsertionSort(int* numbers,int left,int right)
{
	for (int i = left + 1;i <= right;++i)
	{
		int temp = numbers[i];
		int j = i;
		for (;j > left && numbers[j - 1] > temp;--j)
			numbers[j] = numbers[j - 1];
		numbers[j] = temp;
	}
}

void GetLeastKNumberQuick(int* numbers,int left,int right,int k)
{
	if (left + 5 > right)
	{
		InsertionSort(numbers,left,right);
		printKNumbers(numbers,k);
		return;
	}
	int kIndex = k - 1;
	int core = Median3(numbers,left,right);	
	int begin = left,end = right - 1;
	while (true)
	{
		while (numbers[++begin] < core) ;
		while (numbers[--end] > core) ;
		if (begin < end) 
			swap(numbers[begin],numbers[end]);
		else 
			break;
	}
	swap(numbers[begin],numbers[right - 1]);
	if (begin == kIndex)
		printKNumbers(numbers,kIndex);
	else if (begin < kIndex)
		GetLeastKNumberQuick(numbers,begin + 1,right,kIndex);
	else
		GetLeastKNumberQuick(numbers,left,begin - 1,kIndex);
}


void GetLeastKNumber(int* numbers,int length,int k)
{
	if (numbers == NULL || length <= 0 || length < k) return;
	if (length == k)
	{
		printKNumbers(numbers,k);
	}
	else
	{
		GetLeastKNumberQuick(numbers,0,length - 1,k);
	}
}

int main()
{
	int test[] = {4,5,1,6,2,7,3,8};
	GetLeastKNumber(test,8,7);
}
