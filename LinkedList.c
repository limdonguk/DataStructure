#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType
{
  int data;
  struct LinkedListNodeType *pLink; // 다음 노드의 주소를 저장
} LinkedListNode;

typedef struct LinkedListType
{
  int currentCount;
  LinkedListNode headerNode;
} LinkedList;

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

void iterateLinkedList(LinkedList *pList)
{
  int count = 0;
  LinkedListNode *pNode = NULL;

  pNode = &(pList->headerNode);
  while (pNode != NULL)
  {
    printf("[%d], %d\n", count, pNode->data);
    count++;
    pNode = pNode->pLink;
  }
  printf("노드 개수 : %d\n", count);
}

void concatLinkedList(LinkedList *pListA, LinkedList *pListB)
{
  LinkedListNode *pNodeA = NULL;
  if (pListA != NULL && pListB != NULL)
  {
    pNodeA = pListA->headerNode.pLink;

    if (pNodeA != NULL)
    {
      while (pNodeA->pLink != NULL)
      { // pListA 자체는 존재하지만 data가 없을 경우
        pNodeA = pNodeA->pLink;
      }
      pNodeA->pLink = pListB->headerNode.pLink;
    }
    else
    {
      pListA->headerNode.pLink = pListB->headerNode.pLink;
    }
    pListB->headerNode.pLink = NULL;
  }
}

void reverseLinkedList(LinkedList *pList)
{
  LinkedListNode *pNode = NULL;
  LinkedListNode *pPreNode = NULL;
  LinkedListNode *pCurrentNode = NULL;

  if (pList != NULL)
  {
    pNode = &(pList->headerNode);
    while (pNode != NULL)
    {
      pPreNode = pCurrentNode;
      pCurrentNode = pNode;
      pNode = pNode->pLink;
      pCurrentNode->pLink = pPreNode;
    }
    pList->headerNode.pLink = pPreNode;
  }
}
int main(int argc, char *argv[])
{
  LinkedList *pListA = NULL;
  LinkedList *pListB = NULL;

  pListA = createLinkedList();
  pListB = createLinkedList();

  addLinkedListData(pListA, 0, 10);
  addLinkedListData(pListA, 1, 20);
  addLinkedListData(pListA, 2, 30);
  addLinkedListData(pListB, 0, 40);
  addLinkedListData(pListB, 1, 50);

  printf("연결 리스트 결합 전\n");
  printf("연결 리스트 A\n");
  iterateLinkedList(pListA);
  printf("연결 리스트 B\n");
  iterateLinkedList(pListB);

  concatLinkedList(pListA, pListB);
  printf("연결 리스트 결합 후\n");
  printf("연결 리스트 A\n");
  iterateLinkedList(pListA);
  printf("연결 리스트 B");
  iterateLinkedList(pListB);

  deleteLinkedList(pListA);
  deleteLinkedList(pListB);

  return 0;
}
