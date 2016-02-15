#include <stdio.h>

struct ListNode
{
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* LastKthNode(ListNode* pListHead,int k)
{
	if (pListHead == NULL || k <= 0) return NULL;
	ListNode* LastNode = pListHead;
	ListNode* result = pListHead;
	for (int i = 1;i < k;++i)
	{
		if (LastNode->m_pNext != NULL)
		{
			LastNode = LastNode->m_pNext;
		}
		else
		{
			return NULL;
		}
	}
	while (LastNode->m_pNext != NULL)
	{
		LastNode = LastNode->m_pNext;
		result = result->m_pNext;
	}
	return result;
}

int main()
{
	ListNode l3 = {3,NULL};
	ListNode l2 = {2,&l3};
	ListNode l1 = {1,&l2};
	ListNode* test = LastKthNode(&l1,4);
	if (test) printf("%d\n",test->m_nValue);
	else printf("NULL\n");
	return 0;
}
