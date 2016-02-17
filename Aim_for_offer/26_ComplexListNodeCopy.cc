#include <stdio.h>

struct ComplexListNode
{
	int m_nValue;
	ComplexListNode* m_pNext;
	ComplexListNode* m_pSibling;
};

void CloneNextNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != NULL)
	{
		ComplexListNode* pCloneNode = new ComplexListNode();
		pCloneNode->m_nValue = pNode->m_nValue;
		pCloneNode->m_pNext = pNode->m_pNext;
		pCloneNode->m_pSibling = NULL;
		pNode->m_pNext = pCloneNode;
		pNode = pCloneNode->m_pNext;
	}
}

void SetSibing(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != NULL)
	{
		ComplexListNode* pCloneNode = pNode->m_pNext;
		ComplexListNode* Sibling = pNode->m_pSibling;
		if (Sibling != NULL)
		{
			pCloneNode->m_pSibling = Sibling->m_pNext;
		}
		pNode = pCloneNode->m_pNext;
	}
}

ComplexListNode* SeparateNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	ComplexListNode* pCloneNodeHead = pNode->m_pNext;
	ComplexListNode* pCloneNode = pCloneNodeHead;
	ComplexListNode* pNext = pCloneNode->m_pNext;
	pNode->m_pNext = pNext;
	while (pNext != NULL)
	{
		pCloneNode->m_pNext = pNext->m_pNext;
		pNode = pNode->m_pNext;
		pCloneNode = pCloneNode->m_pNext;
		pNext = pCloneNode->m_pNext;
		pNode->m_pNext = pNext;
	}
	return pCloneNodeHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
	if (pHead == NULL) return NULL;
	CloneNextNodes(pHead);
	SetSibing(pHead);
	return SeparateNodes(pHead);
}

void deleteNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != NULL)
	{
		ComplexListNode* pNext = pNode->m_pNext;
		delete pNode;
		pNode = pNext;
	}
}

void printNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != NULL)
	{
		printf("%d ",pNode->m_nValue);
		if (pNode->m_pSibling)
			printf("--->%d",pNode->m_pSibling->m_nValue);
		printf("\n");
		pNode = pNode->m_pNext;;
	}
}
int main()
{
	ComplexListNode l5 = {5,NULL,NULL};
	ComplexListNode l4 = {4,&l5,NULL};
	ComplexListNode l3 = {3,&l4,NULL};
	ComplexListNode l2 = {2,&l3,NULL};
	ComplexListNode l1 = {1,&l2,&l3};
	l5.m_pSibling = &l3;
	l2.m_pNext = NULL;
	ComplexListNode* clone = Clone(&l2);
	printNodes(clone);
	deleteNodes(clone);
}
