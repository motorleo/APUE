#include <stdio.h>

struct ListNode
{
	int m_nValue;
	ListNode* m_pNext;
};

ListNode* ReverseList(ListNode* pListHead)
{
	if (pListHead == NULL) return NULL;
	if (pListHead->m_pNext == NULL) return pListHead;
	ListNode* pPrevious = NULL;
	ListNode* pCurrent = pListHead;
	ListNode* pNext = pCurrent->m_pNext;
	pListHead->m_pNext = NULL;
	while (pNext != NULL)
	{
		pPrevious = pCurrent;
		pCurrent = pNext;
		pNext = pNext->m_pNext;
		pCurrent->m_pNext = pPrevious;
	}
	return pCurrent;
}

ListNode* Reverse(ListNode* Current,ListNode* Next)
{
	if (Next == NULL) return Current;
	ListNode* pPrevious = Current;
	ListNode* pCurrent = Next;
	ListNode* pNext = Next->m_pNext;
	pCurrent->m_pNext = pPrevious;
	return Reverse(pCurrent,pNext);
}

ListNode* ReverseListR(ListNode* pListHead)
{
	if (pListHead == NULL) return NULL;
	if (pListHead->m_pNext == NULL) return pListHead;
	ListNode* pNext = pListHead->m_pNext;
	pListHead->m_pNext = NULL;
	return Reverse(pListHead,pNext);
}

void printList(ListNode* pHead)
{
	ListNode* pCurrent = pHead;
	while (pCurrent != NULL)
	{
		printf("%d ",pCurrent->m_nValue);
		pCurrent = pCurrent->m_pNext;
	}
	printf("\n");
}

int main()
{
	ListNode l3 = {3,NULL};
	ListNode l2 = {2,&l3};
	ListNode l1 = {1,&l2};
	printList(&l1);
	ListNode* head = ReverseListR(&l1);
	printList(head);
	return 0;
}
