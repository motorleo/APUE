
#include <stdio.h>

struct ListNode
{
	    int m_nValue;
		    ListNode* m_pNext;
};


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

