#include <stdio.h>
#include <stdexcept>
#include <string.h>

char FirstOneTimeChar(const char* str,int length)
{
	if (str == NULL || length <= 0)
		throw std::runtime_error("empty input!");
	int hash[256];
	memset(hash,0,256*sizeof(int));
	for (int i = 0;i < length;++i)
	{
		++hash[str[i]];
	}
	char result;
	bool found = false;
	for (int i = 0;i < length;++i)
	{
		if (hash[str[i]] == 1)
		{
			found = true;
			result = str[i];
			break;
		}
	}
	if (found) return result;
	else throw std::runtime_error("invalid input!");
}

int main()
{
	printf("%c\n",FirstOneTimeChar("abba",0));
}
