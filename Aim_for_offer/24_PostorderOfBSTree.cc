#include "BinaryTree.h"

bool PostorderOfBSTree(int* postorder,int length)
{
	if (postorder == NULL || length == 0) return false;
	if (length == 1) return true;
	int root = postorder[length - 1];
	int indexOfRight = 0;
	while (postorder[indexOfRight] < root) ++indexOfRight;
	for (int i = indexOfRight;i < length - 1;++i)
	{
		if (postorder[i] <= root) return false;
	}
	bool left = true;
	if (indexOfRight != 0) 
		left = PostorderOfBSTree(postorder,indexOfRight);
	bool right = true;
	if (indexOfRight != length - 1)
		right = PostorderOfBSTree(postorder+indexOfRight,length-indexOfRight-1);
	return left && right;
}

int main()
{
	int test[] = {5,7,6,9,11,10,8};
	int test1[] = {7,4,6,5};
	if (PostorderOfBSTree(test,7)) printf("True.\n");
	else printf("False.\n");
	if (PostorderOfBSTree(test1,4)) printf("True.\n");
	else printf("False.\n");
}
