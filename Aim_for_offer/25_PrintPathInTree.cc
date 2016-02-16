#include "BinaryTree.h"
#include <vector>

using std::vector;

void PrintPath(BinaryTreeNode* root,int length,vector<int>& NodePath)
{
	bool isLeaf = !root->m_pLeft && !root->m_pRight;
	if (isLeaf)
	{
		if (root->m_nValue == length)
		{
			for (vector<int>::iterator iter = NodePath.begin();
					iter != NodePath.end();++iter)
				printf("%d ",*iter);
			printf("%d\n",length);
		}
	}
	else if (root->m_nValue < length)
	{
		NodePath.push_back(root->m_nValue);
		if (root->m_pLeft)
		{
			PrintPath(root->m_pLeft,length - root->m_nValue,NodePath);
		}
		if (root->m_pRight)
		{
			PrintPath(root->m_pRight,length - root->m_nValue,NodePath);
		}
		NodePath.pop_back();
	}
}

void PrintPathInTree(BinaryTreeNode* root,int length)
{
	if (root == NULL || length == 0) return;
	vector<int> NodePath;
	PrintPath(root,length,NodePath);
}

int main()
{
	BinaryTreeNode t1 = {1,NULL,NULL};
	BinaryTreeNode t4 = {4,NULL,NULL};
	BinaryTreeNode t7 = {7,&t1,NULL};
	BinaryTreeNode t5 = {5,&t4,&t7};
	BinaryTreeNode t12 = {12,NULL,NULL};
	BinaryTreeNode t10 = {10,&t5,&t12};
	PrintPathInTree(&t10,22);
}
