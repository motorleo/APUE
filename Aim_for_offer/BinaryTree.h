#include <stdio.h>
#include <deque>

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

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

