#include <stdio.h>
#include <stdexcept>

struct BinaryTreeNode
{
	int				m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

BinaryTreeNode* BuildBinaryTree(int* preOrder,int* inOrder,int length)
{
	if (preOrder == NULL || inOrder == NULL || length <= 0) return NULL;
	int rootValue = preOrder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->m_nValue = rootValue;
	if (length == 1)
	{
		if (*preOrder != *inOrder) throw std::invalid_argument("invail input.");
		root->m_pLeft = NULL;
		root->m_pRight = NULL;
	}
	else
	{
		int LengthOfLeft = 0;
		while (LengthOfLeft < length && inOrder[LengthOfLeft] != rootValue) 
			++LengthOfLeft;
		if (LengthOfLeft == length) throw std::invalid_argument("invail input!");
		root->m_pLeft = BuildBinaryTree(preOrder+1,inOrder,LengthOfLeft);
		root->m_pRight = BuildBinaryTree(
			preOrder+LengthOfLeft+1,inOrder+LengthOfLeft+1,length-LengthOfLeft-1);
	}
	return root;
}

void prePrintTree(BinaryTreeNode* root)
{
	if (root == NULL) return;
	printf("%d ",root->m_nValue);
	prePrintTree(root->m_pLeft);
	prePrintTree(root->m_pRight);
}

void inPrintTree(BinaryTreeNode* root)
{
	if (root == NULL) return;
	inPrintTree(root->m_pLeft);
	printf("%d ",root->m_nValue);
	inPrintTree(root->m_pRight);
}

void postPrintTree(BinaryTreeNode* root)
{
	if (root == NULL) return;
	postPrintTree(root->m_pLeft);
	postPrintTree(root->m_pRight);
	printf("%d ",root->m_nValue);
	delete root;
}

int main()
{
	int pre[] = {1,2,4,7};
	int in[] = {1,2,4,7};
	BinaryTreeNode* l1 = BuildBinaryTree(pre,in,4);
	printf("pre:");
	prePrintTree(l1);
	printf("\nin:");
	inPrintTree(l1);
	printf("\npost:");
	postPrintTree(l1);
	printf("\n");
	//if (l1 != NULL) delete l1;
	return 0;
}
