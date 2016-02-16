#include <stdio.h>

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

bool ANodeHasBNode(BinaryTreeNode* A,BinaryTreeNode* B)
{
	if (B == NULL) return true;
	else if (A == NULL) return false;
	if (A->m_nValue == B->m_nValue)
	{
		return ANodeHasBNode(A->m_pLeft,B->m_pLeft) && 
			   ANodeHasBNode(A->m_pRight,B->m_pRight);
	}
	else
	{
		return false;
	}
}

bool ATreeHasBTree(BinaryTreeNode* A,BinaryTreeNode* B)
{
	if (B == NULL) return true;//can change
	else if (A == NULL) return false;
	bool result = false;
   	if (A->m_nValue == B->m_nValue)
	{
		result = ANodeHasBNode(A,B);
	}
	if (!result)
	{
		result = ATreeHasBTree(A->m_pLeft,B) || ATreeHasBTree(A->m_pRight,B);
	}
	return result;
}
