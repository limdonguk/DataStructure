#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

BinTreeNode* makeNewNodeBT(char data) {
    BinTreeNode *pReturn = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    if(pReturn != NULL) {
        pReturn->data = data;
        pReturn->pLeftChild = NULL;
        pReturn->pRightChild = NULL;
    }
    return pReturn;
}

BinTree* makeBinTree(char rootNodeData) {
    BinTree *pReturn = NULL;
    pReturn = (BinTree*)malloc(sizeof(BinTree));
    if(pReturn != NULL) {
        pReturn->pRootNode = makeNewNodeBT(rootNodeData);
        if(pReturn->pRootNode == NULL) {
            free(pReturn);
            pReturn = NULL;
            printf("오류, 메모리할당\n");
        }
    }
    else {
        printf("오류, 메모리할당\n");
    }
    return pReturn;
}

BinTreeNode* addLeftChildNodeBT(BinTreeNode* pParentNode, char data) {
    BinTreeNode* pReturn = NULL;
    if(pParentNode != NULL) {
        if(pParentNode->pLeftChild == NULL) {
            pParentNode->pLeftChild = makeNewNodeBT(data);
            pReturn = pParentNode->pLeftChild;
            
        }
        else {
            printf("오류, 이미 노드가 존재합니다.\n");
        }
    }
    return pReturn;
}

BinTreeNode* addRightChildNodeBT(BinTreeNode* pParentNode, char data) {
    BinTreeNode* pReturn = NULL;
    if(pParentNode != NULL) {
        if(pParentNode->pRightChild == NULL) {
            pParentNode->pRightChild = makeNewNodeBT(data);
            pReturn = pParentNode->pRightChild;
        }
        else {
            printf("오류, 이미 노드가 존재합니다.");
        }
    }
    return pReturn;
}

BinTreeNode* getRootNodeBT(BinTree* pBinTree) {
    BinTreeNode* pReturn = NULL;
    if(pBinTree != NULL) {
        pReturn = pBinTree->pRootNode;
    }
    return pReturn;
}

void deleteBinTreeNode(BinTreeNode* pNode) {
    if(pNode != NULL) {
        deleteBinTreeNode(pNode->pLeftChild);
        deleteBinTreeNode(pNode->pRightChild);
        free(pNode);
    }
}

void deleteBinTree(BinTree* pBinTree) {
    if(pBinTree != NULL) {
        deleteBinTreeNode(pBinTree->pRootNode);
        free(pBinTree);
    }
}
