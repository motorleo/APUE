#include "ListNode.h"
#include <stdexcept>

ListNode* FirstCommonNode(ListNode* list1,ListNode* list2)
{
	if (list1 == NULL || list2 == NULL)
		throw std::invalid_argument("invalid input!");
	int length1 = 0;
	int length2 = 0;
	ListNode* left = list1;
	ListNode* right = list2;
	while (left)
	{
		++length1;
		left = left->m_pNext;
	}
	while (right)
	{
		++length2;
		right = right->m_pNext;
	}
	left = list1;
	right = list2;
	if (length1 > length2)
	{
		for (int i = 0;i < length1 - length2;++i)
			left = left->m_pNext;
	}
	else 
	{
		for (int i = 0;i < length2 - length1;++i)
			right = right->m_pNext;
	}
	while (left)
	{
		if (left == right) return left;
		left = left->m_pNext;
		right = right->m_pNext;
	}
	return NULL;
}

int main()
{
	ListNode l5 = {5,NULL};
	ListNode l4 = {4,NULL};
	ListNode l3 = {3,&l4};
	ListNode l2 = {2,&l4};
	ListNode l1 = {1,&l2};
	ListNode* test = FirstCommonNode(&l3,&l5);
	if (test)
		printf("%d\n",test->m_nValue);
}
