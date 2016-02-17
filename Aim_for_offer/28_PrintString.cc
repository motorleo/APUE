#include <stdio.h>
#include <string.h>
#include <algorithm>

using std::swap;

void PrintString(char* string,int length,int index)
{
	if (index == length - 1)
	{
		printf("%s\n",string);
		return;
	}
	PrintString(string,length,index + 1);
	for (int i = index + 1;i < length;++i)
	{
		swap(string[index],string[i]);
		PrintString(string,length,index + 1);
		swap(string[index],string[i]);
	}
}

void PrintString(const char* string)
{
	if (string == NULL) return;
	int len = strlen(string);
	char str[len + 1];
	strcpy(str,string);//must not be NULL
	PrintString(str,len,0);
}

int main()
{
	PrintString(NULL);
}
