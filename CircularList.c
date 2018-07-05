#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CircularListNodeType {
    int data;
    struct CircularListNode* pLink;
} CircularListNode;

typedef struct CircularListType {
    int currentCount;
    CircularListNode headerNode;
} CircularList;

CircularList *createCircluarList() {
    CircularList *pReturn = (CircularList*)malloc(sizeof(CircularList));
    memset(pReturn, 0, sizeof(CircularList));
    return pReturn;
}

int getCircularListData(CircularList *pList, int position) {
    CircularListNode *pCurrentNode = &(pList->headerNode);
    for(int i=0; i<=position; i++) {
        pCurrentNode = pCurrentNode->pLink;
    }
    return pCurrentNode->data;
}

int addCircularListData(CircularList *pList, int position, int data) {
    CircularListNode *pNewNode = NULL;
    CircularListNode *pPreNode = NULL;

    pNewNode = (CircularListNode*)malloc(sizeof(CircularListNode));
    pNewNode->data = data;

    pPreNode = &(pList->headerNode);
    for(int i=0; i<position; i++) {
        pPreNode = pPreNode->pLink;
    }

    pNewNode->pLink = pPreNode->pLink;
    pPreNode->pLink = pNewNode;

    pList->currentCount++;
    if(pNewNode->pLink == NULL) {
        pNewNode->pLink = pNewNode;
    }

    return 0;
}

int removeCircularListData(CircularList *pList, int position) {
    CircularListNode *pDelNode = NULL;
    CircularListNode *pPreNode = NULL;

    pPreNode = &(pList->headerNode);
    for(int i=0; i<position; i++) {
        pPreNode = pPreNode->pLink;
    }

    pDelNode = pPreNode->pLink;
    pPreNode->pLink = pDelNode->pLink;

    pList->currentCount--;
    if(pList->currentCount == 0) {
        pList->headerNode.pLink = NULL;
    }
    free(pDelNode);

    return 0;
}