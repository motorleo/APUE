#include <stdio.h>
#include "BinaryTree.h"
#include <deque>

void BFSPrintTree(BinaryTreeNode* root)
{
	if (root == NULL) return;
	std::deque<BinaryTreeNode*> queue;
	queue.push_back(root);
	while (!queue.empty())
	{
		BinaryTreeNode* currentNode = queue.front();
		queue.pop_front();
		printf("%d ",currentNode->m_nValue);
		if (currentNode->m_pLeft) queue.push_back(currentNode->m_pLeft);
		if (currentNode->m_pRight) queue.push_back(currentNode->m_pRight);
	}
	printf("\n");
}

int main()
{
	BinaryTreeNode t11 = {11,NULL,NULL};
	BinaryTreeNode t5 = {5,NULL,NULL};
	BinaryTreeNode t9 = {9,NULL,NULL};
	BinaryTreeNode t7 = {7,NULL,NULL};
	BinaryTreeNode t6 = {6,&t5,NULL};
	BinaryTreeNode t10 = {10,&t9,NULL};
	BinaryTreeNode t8 = {8,&t6,NULL};
	BFSPrintTree(&t8);
}
