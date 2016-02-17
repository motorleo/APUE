#include "BinaryTree.h"

BinaryTreeNode* BSTConvert(BinaryTreeNode* root,BinaryTreeNode** pLastNode)
{
	BinaryTreeNode* pHead = NULL;
	//left subtree
	BinaryTreeNode* left = NULL;//for connect
	if (root->m_pLeft) 
		pHead = BSTConvert(root->m_pLeft,&left);
	else 
		pHead = root;
	//right subtree
	BinaryTreeNode* right = NULL;//for connect
	if (root->m_pRight != NULL)
		right = BSTConvert(root->m_pRight,pLastNode);
	else
		*pLastNode = root;
	//connect
	root->m_pLeft = left;
	root->m_pRight = right;
	if (left != NULL)
		left->m_pRight = root;
	if (right != NULL)
		right->m_pLeft = root;
	return pHead;
}

BinaryTreeNode* BSTConvert(BinaryTreeNode* root)
{
	if (root == NULL) return NULL;
	BinaryTreeNode* pLastNode = NULL;
	return BSTConvert(root,&pLastNode);
}

void print(BinaryTreeNode* pHead)
{
	BinaryTreeNode* pNode = pHead;
	while (pNode->m_pRight)
	{
		printf("%d ",pNode->m_nValue);
		pNode = pNode->m_pRight;
	}
	while (pNode)
	{
		printf("%d ",pNode->m_nValue);
		pNode = pNode->m_pLeft;
	}
	printf("\n");
}

int main()
{
	BinaryTreeNode t4 = {4,NULL,NULL};
	BinaryTreeNode t8 = {8,NULL,NULL};
	BinaryTreeNode t12 = {12,NULL,NULL};
	BinaryTreeNode t16 = {16,NULL,NULL};
	BinaryTreeNode t6 = {6,&t4,&t8};
	BinaryTreeNode t14 = {14,&t12,&t16};
	BinaryTreeNode t10 = {10,&t6,&t14};
	BinaryTreeNode* pHead = BSTConvert(&t10);
	print(pHead);
}
