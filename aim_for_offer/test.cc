#include <stdio.h>

class test
{
};

int main()
{
	test a;
	test b;
	if (a == b) printf("OK");
	else printf("Not OK");
	return 0;
}
