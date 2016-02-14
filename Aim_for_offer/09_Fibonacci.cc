#include <stdio.h>

long long Fibonacci(int n)
{
	if (n <= 0) return 0;
	if (n == 1) return 1;
	long long last = 0;
	long long near = 1;
	long long current;
	for (int i = 2;i <= n;++i)
	{
		current = last + near;
		last = near;
		near = current;	
	}
	return current;
}

long long frog(int n)
{
	if (n <= 0) return 0;
	if (n == 1) return 1;
	if (n == 2) return 2;
	long long last = 1;
	long long near = 2;
	long long current;
	for (int i = 3;i <= n;++i)
	{
		current = last + near;
		last = near;
		near = current;	
	}
	return current;
}

int main()
{
	for (int i = 0;i < 20;++i)
		printf("%lld\n",Fibonacci(i));
	return 0;
}
