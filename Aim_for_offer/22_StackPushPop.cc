#include <stdio.h>
#include <stack>

bool PopWithPush(int* pPush,int* pPop,int length)
{
	if (pPush == NULL || pPop == NULL || length <= 0) return false;
	std::stack<int> Stack;
	int indexOfPush = 0;
	for (int indexOfPop = 0;indexOfPop < length;++indexOfPop)
	{
		int value = pPop[indexOfPop];
		if (!Stack.empty() && Stack.top() == value)
		{
			Stack.pop();
		}
		else
		{
			while (indexOfPush < length && pPush[indexOfPush] != value)
			{
				Stack.push(pPush[indexOfPush]);
				++indexOfPush;
			}
			if (indexOfPush == length) return false;
			++indexOfPush;
		}
	}
	return true;
}

int main()
{
	int push1[] = {1,2,3,4,5};
	int pop1[] = {4,5,3,2,1};
	int pop2[] = {4,3,5,1,2};
	int push2[] = {1};
	int pop3[] = {2};
	if (PopWithPush(push1,pop1,5)) printf("True.\n");
	else printf("False.\n");
	if (PopWithPush(push1,pop2,5)) printf("True.\n");
	else printf("False.\n");
	if (PopWithPush(push2,push2,1)) printf("True.\n");
	else printf("False.\n");
	if (PopWithPush(push2,pop3,1)) printf("True.\n");
	else printf("False.\n");
	return 0;
}
