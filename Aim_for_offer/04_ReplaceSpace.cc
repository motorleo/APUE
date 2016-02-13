#include <string.h>
#include <stdio.h>

void replaceSpace(char* str,int length)
{
	if (str == NULL || length < 0) return;
	int oldLen = strlen(str);//size_t
	int n = 0;
	for (int i = 0;i < oldLen;++i) 
		if (str[i] == ' ') ++n;
	int newLen = oldLen + n*2;
	if (length < newLen + 1) return;
	int indexOld = oldLen;
	int indexNew = newLen;
	while (indexOld >= 0 && indexNew > indexOld)
	{
		if (str[indexOld] == ' ')
		{
			str[indexNew--] = '0';
			str[indexNew--] = '2';
			str[indexNew--] = '%';
		}
		else
		{
			str[indexNew--] = str[indexOld];
		}
		--indexOld;
	}
}

int main()
{
	char str[40] = "";
	printf("%s:%lu\n",str,strlen(str));
	replaceSpace(str,40);
	printf("%s:%lu\n",str,strlen(str));
	return 0;
}
