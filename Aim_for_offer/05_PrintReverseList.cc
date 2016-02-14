#include <stack>
#include <stdio.h>

struct ListNode
{
	int m_nKey;
	ListNode* m_pNext;
};

void PrintReverseList(ListNode* head)
{
	std::stack<int> Stack;
	ListNode* current = head;
	while (current != NULL)
	{
		Stack.push(current->m_nKey);
		current = current->m_pNext;
	}
	while (!Stack.empty())
	{
		printf("%d\n",Stack.top());
		Stack.pop();
	}
}

int main()
{
	ListNode l2 = {2,NULL};
	ListNode l1 = {1,&l2};
	PrintReverseList(&l1);
	return 0;
}
