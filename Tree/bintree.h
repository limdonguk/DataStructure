#ifndef _BINTREE_
#define _BINTREE_

typedef struct BinTreeNodeType {
    char data;
    struct BinTreeNodeType* pLeftChild;  // 왼쪽 자식 노드를 가리키는 포인터 변수
    struct BinTreeNodeType* pRightChild; // 오른쪽 자식 노드를 가리키는 포인터 변수 
} BinTreeNode;

typedef struct BinTreeType {
    struct BinTreeNodeType *pRootNode;   // 루트 노드를 가르키는 트리의 포인터
} BinTree;

BinTreeNode* makeNewNodeBT(char data);
BinTree* makeBinTree(char rootNodeData);
BinTreeNode* addLeftChildNodeBT(BinTreeNode* pParentNode, char data);
BinTreeNode* addRightChildNodeBT(BinTreeNode* pParentNode, char data);
BinTreeNode* getRootNodeBT(BinTree* pBinTree);
void deleteBinTreeNode(BinTreeNode* pNode);
void deleteBinTree(BinTree* pBinTree);

#endif