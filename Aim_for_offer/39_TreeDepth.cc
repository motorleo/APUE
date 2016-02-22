#include "BinaryTree.h"
#include <stdexcept>

int TreeDepth(BinaryTreeNode* root)
{
	if (root == NULL)
		return 0;
	int left = TreeDepth(root->m_pLeft);
	int right = TreeDepth(root->m_pRight);
	return left > right ? (left + 1) : (right + 1);
}

bool IsBalance(BinaryTreeNode* root,int* depth)
{
	if (root == NULL)
		return false;
	if (depth == NULL)
		throw std::invalid_argument("invalid argument!");
	int leftDepth = 0;
	int rightDepth = 0;
	bool left = true;
	bool right = true;
	if (root->m_pLeft)
		left = IsBalance(root->m_pLeft,&leftDepth);
	if (!left) return false;
	if (root->m_pRight)
		right = IsBalance(root->m_pRight,&rightDepth);
	if (!right) return false;
	*depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
	if (-1 <= leftDepth - rightDepth && leftDepth - rightDepth <= 1)
		return true;
	else 
		return false;
}

bool IsBalance(BinaryTreeNode* root)
{
	int depth;
	return IsBalance(root,&depth);
}

int main()
{
	BinaryTreeNode t5 = {5,NULL,NULL};
	BinaryTreeNode t7 = {7,NULL,NULL};
	BinaryTreeNode t9 = {9,NULL,NULL};
	BinaryTreeNode t11 = {11,NULL,NULL};
	BinaryTreeNode t6 = {6,&t5,&t7};
	BinaryTreeNode t10 = {10,&t9,&t11};
	BinaryTreeNode t8 = {8,&t6,NULL};
	if (IsBalance(&t8))
		printf("yes\n");
	else
		printf("no\n");
}
