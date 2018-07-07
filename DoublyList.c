// DoublyList.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoublyListNodeType
{
    int data;
    struct DoublyListNodeType *pLLink;
    struct DoublyListNodeType *pRLink;
} DoublyListNode;

typedef struct DoublyListType
{
    int currentCount;
    DoublyListNode headerNode;
} DoublyList;

DoublyList *createDoublyList()
{
    DoublyList *pReturn = (DoublyList *)malloc(sizeof(DoublyList));
    if (pReturn != NULL)
    {
        memset(pReturn, 0, sizeof(DoublyList));
        pReturn->headerNode.pLLink = &(pReturn->headerNode);
        pReturn->headerNode.pRLink = &(pReturn->headerNode);
    }
    return pReturn;
}

int getDoublyListData(DoublyList *pList, int position)
{
    if (pList != NULL)
    {
        if (position >= 0 && position < pList->currentCount)
        {
            DoublyListNode *pNode = &(pList->headerNode);
            for (int i = 0; i <= position; i++)
            {
                pNode = pNode->pRLink;
            }
            return pNode->data;
        }
    }
}

int addDoublyListData(DoublyList *pList, int position, int data)
{
    DoublyListNode *pPreNode = NULL;
    DoublyListNode *pNewNode = NULL;

    pNewNode = (DoublyListNode *)malloc(sizeof(DoublyListNode));
    if (pNewNode != NULL)
    {
        memset(pNewNode, 0, sizeof(DoublyListNode));
        pNewNode->data = data;

        pPreNode = &(pList->headerNode);
        for (int i = 0; i < position; i++)
        {
            pPreNode = pPreNode->pRLink;
        }

        pNewNode->pRLink = pPreNode->pRLink; // 추가된 노드 처리
        pNewNode->pLLink = pPreNode;

        pPreNode->pRLink = pNewNode; // 기존의 노드 처리
        pNewNode->pRLink->pLLink = pNewNode;

        pList->currentCount++;
    }
    else
    {
        printf("메모리 할당 오류");
        return 1;
    }
    return 0;
}

int removeDoublyListData(DoublyList *pList, int position)
{
    DoublyListNode *pPreNode = NULL;
    DoublyListNode *pDelNode = NULL;

    pPreNode = &(pList->headerNode);
    for (int i = 0; i < position; i++)
    {
        pPreNode = pPreNode->pRLink;
    }

    pDelNode = pPreNode->pRLink;
    pPreNode->pRLink = pDelNode->pRLink;
    pDelNode->pRLink->pLLink = pPreNode;

    free(pDelNode);
    pList->currentCount--;

    return 0;
}

int getDoublyListLength(DoublyList *pList)
{
    if (pList != NULL)
    {
        return pList->currentCount;
    }
    return 0;
}

void displayDoublyListData(DoublyList *pList)
{
    DoublyListNode *pNode = NULL;
    pNode = pList->headerNode.pRLink;
    if (pList->currentCount == 0)
    {
        printf("자료가 없습니다.");
    }
    else
    {
        printf("노드 개수 : %d \n", pList->currentCount);
        for (int i = 0; i < pList->currentCount; i++)
        {
            printf("[%d], %d\n", i, pNode->data);
            pNode = pNode->pRLink;
        }
    }
}

void deleteDoublyList(DoublyList *pList)
{
    if (pList != NULL)
    {
        while (pList->currentCount > 0)
        {
            removeDoublyListData(pList, 0);
        }
        free(pList);
    }
}

int main(int argc, char *argv[])
{
    DoublyList *pList = createDoublyList();
    if (pList != NULL)
    {
        addDoublyListData(pList, 0, 10);
        addDoublyListData(pList, 1, 20);
        addDoublyListData(pList, 2, 30);
        displayDoublyListData(pList);

        removeDoublyListData(pList, 0);
        displayDoublyListData(pList);

        deleteDoublyList(pList);
    }

    return pList;
}