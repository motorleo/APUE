#include <stdio.h>

int main()
{
	char str[10] = "hallo";
	printf("%d",str[11]);
	str[5] = 's';
	printf("%d",str[6]);
	return 0;
}
