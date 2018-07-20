#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

//--------------------------전위 순회-------------------------
void preorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode) {
    if(pNode != NULL) {
        printf("%c",pNode->data);                                    // V(현재)
        preorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);    // L(왼쪽)
        preorderTraversalRecursiveBinTreeNode(pNode->pRightChild);   // R(오른쪽)
    }
}

void preorderTraversalRecursiveBinTree(BinTree *pBinTree) {
    if(pBinTree != NULL) {
        preorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

//--------------------------중위 순회-------------------------
void inorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode) {
    if(pNode != NULL) { 
        inorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);    // L(왼쪽)
        printf("%c",pNode->data);                                   // V(현재)
        inorderTraversalRecursiveBinTreeNode(pNode->pRightChild);   // R(오른쪽)
    }
}

void inorderTraversalRecursiveBinTree(BinTree *pBinTree) {
    if(pBinTree != NULL) {
        inorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}

//--------------------------후위 순회-------------------------
void pastorderTraversalRecursiveBinTreeNode(BinTreeNode *pNode) {
    if(pNode != NULL) {
        pastorderTraversalRecursiveBinTreeNode(pNode->pLeftChild);    // L(왼쪽)
        pastorderTraversalRecursiveBinTreeNode(pNode->pRightChild);   // R(오른쪽)
        printf("%c",pNode->data);                                     // V(현재)
    }
}

void pastorderTraversalRecursiveBinTree(BinTree *pBinTree) {
    if(pBinTree != NULL) {
        pastorderTraversalRecursiveBinTreeNode(pBinTree->pRootNode);
        printf("\n");
    }
}
//------------------------------------------------------------

int main(int argc, char* argv[]) {
    BinTree *pBinTree = NULL;
    BinTreeNode *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;

    pBinTree = makeBinTree('A');
    if(pBinTree != NULL) {
        pNodeA = getRootNodeBT(pBinTree);
		pNodeB = addLeftChildNodeBT(pNodeA, 'B');
		pNodeC = addRightChildNodeBT(pNodeA, 'C');
		if (pNodeB != NULL) {
			addLeftChildNodeBT(pNodeB, 'D');
			addRightChildNodeBT(pNodeB, 'E');
		}
		if (pNodeC != NULL) {
			addLeftChildNodeBT(pNodeC, 'F');
			addRightChildNodeBT(pNodeC, 'G');
		}
    }

    if(pBinTree != NULL) {
        printf("전위 순회 결과 : ");
        preorderTraversalRecursiveBinTree(pBinTree);
        printf("중위 순회 결과 : ");
        inorderTraversalRecursiveBinTree(pBinTree);
        printf("후위 순회 결과 : ");
        pastorderTraversalRecursiveBinTree(pBinTree);

        deleteBinTree(pBinTree);
    }

    return 0;
}
