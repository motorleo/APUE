#include <stdio.h>
#include <algorithm>

void ReorderArray(int* array,int length)
{
	if (array == NULL || length <= 1) return;
	int* begin = array;
	int* end = array + (length - 1);
	while (true)
	{
		while (*begin & 1 && begin < end) ++begin;
		while (!(*end & 1) && begin < end) --end;
		if (begin < end) 
		{
			using std::swap;
			swap(*begin,*end);
		}
		else
		{
			break;
		}
	}
}

int main()
{
	int test[] = {1,3,5,7,9};
	ReorderArray(test,5);
	for (int i = 0;i != 5;++i)
		printf("%d ",test[i]);
	return 0;
}
