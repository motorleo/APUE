#include <stdio.h>
#include <string.h>

void Reverse(char* begin,char* end)
{
	if (!begin || !end) return;
	--end;
	while (begin < end)
	{
		char temp = *begin;
		*begin = *end;
		*end = temp;
		++begin;
		--end;
	}
}

void ReverseWords(char* str)
{
	if (str == NULL || *str == '\0') return;
	char* begin = str;
	char* end = begin;
	while (*end != '\0')
		++end;
	Reverse(begin,end);

	begin = end = str;
	while (*end != '\0')
	{
		end = begin + 1;
		while (true)
		{
			if (*end == '\0' || *end == ' ')
				break;
			++end;
		}
		Reverse(begin,end);
		if (*end != '\0')
			begin = end + 1;
	}
}

void rotateWords(char* str,int k)
{
	if (str == NULL || *str == '\0') return;
	if (strlen(str) <= k || k <= 0) return;
	char* begin = str;
	char* end = begin;
	while (*end != '\0')
		++end;
	char* rightStr = begin + k;
	Reverse(begin,rightStr);
	Reverse(rightStr,end);
	Reverse(begin,end);
}

int main()
{
	char test[15] = "I am a worker.";
	rotateWords(test,3);
	printf("%s\n",test);
}
