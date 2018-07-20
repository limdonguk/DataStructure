#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

LinkedList *createLinkedList()
{
    LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList)); // malloc은 실패할 경우 NULL 반환
    if (pReturn != NULL)
    { // NULL 이 아닐 경우에만 memset
        memset(pReturn, 0, sizeof(LinkedList));
    }
    else
    {
        printf("메모리 할당 에러 createLinkedList\n");
    }
    return pReturn;
}

int getLinkedListData(LinkedList *pList, int position)
{
    int i = 0;
    LinkedListNode *pCurrentNode = &(pList->headerNode);

    for (i = 0; i <= position; i++)
    {
        pCurrentNode = pCurrentNode->pLink;
    }

    return pCurrentNode->data;
}

int addLinkedListData(LinkedList *pList, int position, int data)
{
    if (pList != NULL)
    { // 리스트 점검
        if (position > 0 && position <= pList->currentCount)
        { // 입력 Parameter의 유효값 점검
            int i = 0;
            LinkedListNode *pNewNode = NULL;
            LinkedListNode *pPreNode = NULL;

            pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
            pNewNode->data = data;

            pPreNode = &(pList->headerNode); //헤더 노드 부터 입력한 position의 '이전노드'까지 이동.
            for (i = 0; i < position; i++)
            {
                pPreNode = pPreNode->pLink;
            }

            pNewNode->pLink = pPreNode->pLink; // 다음 노드의 처리
            pPreNode->pLink = pNewNode;        // 이전 노드의 처리
            pList->currentCount++;             // 현재 노드 개수 1개 증가.

            return 0;
        }
    }
}

int removeLinkedListData(LinkedList *pList, int position)
{
    int i = 0;
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = NULL;

    pPreNode = &(pList->headerNode);
    for (i = 0; i < position; i++)
    {
        pPreNode = pPreNode->pLink;
    }

    pDelNode = pPreNode->pLink;        // 제거하려는 노드 지정
    pPreNode->pLink = pDelNode->pLink; // 이전 노드의 처리
    free(pDelNode);                    // 제거 노드의 메모리 해제
    pList->currentCount--;             // 현재 노드의 개수 1 감소

    return 0;
}

void deleteLinkedList(LinkedList *pList)
{
    LinkedListNode *pDelNode = NULL;
    LinkedListNode *pPreNode = pList->headerNode.pLink;

    while (pPreNode != NULL)
    {
        pDelNode = pPreNode;
        free(pDelNode);
        pPreNode = pPreNode->pLink;
    }
    free(pList);
}

int getLinkedListLength(LinkedList *pList)
{
    if (pList != NULL)
    {
        return pList->currentCount;
    }
    return 0;
}