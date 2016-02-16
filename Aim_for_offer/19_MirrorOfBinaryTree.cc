#include "BinaryTree.h"

BinaryTreeNode* Mirror(BinaryTreeNode* root)
{
	if (root == NULL) return NULL;
	BinaryTreeNode* left = root->m_pLeft;
	BinaryTreeNode* right = root->m_pRight;
	root->m_pLeft = Mirror(right);
	root->m_pRight = Mirror(left);
	return root;
}
