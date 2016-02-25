#include <stdio.h>

int add(int lhs,int rhs)
{
	if (lhs == 0) return rhs;
	if (rhs == 0) return lhs;
	return add(lhs ^ rhs,(lhs & rhs) << 1);
}

int main()
{
	printf("%d\n",add(3,4));
}
