#include <stdio.h>

struct ListNode
{
	int		m_nValue;
	ListNode* m_pNext;
};

void DeleteNode(ListNode** pListHead,ListNode* pToBeDelete)
{
	if (pToBeDelete == NULL || pListHead == NULL) return;
	if (pToBeDelete->m_pNext != NULL)
	{
		ListNode* pNext = pToBeDelete->m_pNext;
		pToBeDelete->m_nValue = pNext->m_nValue;
		pToBeDelete->m_pNext = pNext->m_pNext;
		delete pNext;
	}
	else if (*pListHead != pToBeDelete)
	{
		ListNode* currentNode = *pListHead;
		while (currentNode->m_pNext != pToBeDelete) 
			currentNode = currentNode->m_pNext;
		currentNode->m_pNext = NULL;
		delete pToBeDelete;
		pToBeDelete = NULL;
	}
	else
	{
		delete pToBeDelete;
		*pListHead = NULL;
		pToBeDelete = NULL;
	}
}

int main()
{
	DeleteNode(NULL,NULL);
	return 0;
}
