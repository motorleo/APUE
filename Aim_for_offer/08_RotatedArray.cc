#include <stdio.h>
#include <vector>
#include <stdexcept>

int Min(int* begin,int* end)
{
	int result;
	if (end - begin == 1) 
	{
		result = *end;
	}
	else 
	{
		int* midNum	= begin + (end - begin)/2;
		if (*midNum < *begin)
		{
			result = Min(begin,midNum);
		}
		else if (*midNum > *begin)
		{
			result = Min(midNum,end);
		}
		else
		{
			int* iter = begin;
			result = *(iter++);
			while (iter <= end)
			{
				if (*iter < result) result = *iter;
				++iter;
			}
		}
	}
	return result;
}

int RotateArray(int* numbers,int length)
{
	if (numbers == NULL || length <= 0) throw std::runtime_error("invalid input.");
	int result;
	if (length == 1) 
	{
		result = numbers[0];
	}
	else if (numbers[0] < numbers[length - 1])
	{
		result = numbers[0];
	}
	else
	{
		result = Min(numbers,numbers + (length - 1));
	}
	return result;
}



int main()
{
	int test[5] = {4,5,6,2,3};
	printf("%d\n",RotateArray(test,5));
	int test1[5] = {1,2,3,4,5};
	printf("%d\n",RotateArray(test1,5));
	int test2[5] = {1,2,3,4,0};
	printf("%d\n",RotateArray(test2,5));
	int test3[5] = {1,1,0,1,1};
	printf("%d\n",RotateArray(test3,5));
	return 0;
}
