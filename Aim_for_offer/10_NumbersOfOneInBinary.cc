#include <stdio.h>

int NumbersOfOne(int num)
{
	int count = 0;
	unsigned flag = 1;
	while (flag)
	{
		if (num & flag)
			++count;
		flag = flag << 1;
	}
	return count;
}

int main()
{
	printf("0:%d\n",NumbersOfOne(0));
	printf("1:%d\n",NumbersOfOne(1));
	printf("9:%d\n",NumbersOfOne(9));
	printf("0x80000000:%d\n",NumbersOfOne(0x80000000));
	printf("0xFFFFFFFF:%d\n",NumbersOfOne(0xFFFFFFFF));
	printf("0x7FFFFFFF:%d\n",NumbersOfOne(0x7FFFFFFF));
	return 0;
}
