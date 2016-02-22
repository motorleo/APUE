#include <stdio.h>
#include <stdexcept>

void NumbersAppearOnce(int* numbers,int length)
{
	if (!numbers || length <= 1) 
		throw std::invalid_argument("invalid input!");
	int base = 0;
	for (int i = 0;i < length;++i)
		base ^= numbers[i];
	unsigned int seperateBase = 1;
	while (!(base & 1))
	{
		base = base >> 1;
		seperateBase = seperateBase << 1;
	}
	int NumLeft = 0;
	int NumRight = 0;
	for (int i = 0;i < length;++i)
	{
		if (numbers[i] & seperateBase)
			NumLeft ^= numbers[i];
		else
			NumRight ^= numbers[i];
	}
	printf("%d %d\n",NumLeft,NumRight);
}

int main()
{
	int test[] = {2,4,3,6,3,2,5,5};
	NumbersAppearOnce(test,1);
}
