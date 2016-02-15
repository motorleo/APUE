#include <stdio.h>
#include "ListNode.h"

ListNode* MergeSortedList(ListNode* pHead1,ListNode* pHead2)
{
	if (pHead1 == NULL) return pHead2;
	else if (pHead2 == NULL) return pHead1;
	ListNode* result = NULL;
	if (pHead1->m_nValue <= pHead2->m_nValue)
	{
		result = pHead1;
		result->m_pNext = MergeSortedList(pHead1->m_pNext,pHead2);
	}
	else
	{
		result = pHead2;
		result->m_pNext = MergeSortedList(pHead1,pHead2->m_pNext);
	}
	return result;
}
