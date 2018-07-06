#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CircularListNodeType
{
  int data;
  struct CircularListNode *pLink;
} CircularListNode;

typedef struct CircularListType
{
  int currentCount;
  CircularListNode headerNode;
} CircularList;

CircularList *createCircluarList()
{
  CircularList *pReturn = (CircularList *)malloc(sizeof(CircularList));
  memset(pReturn, 0, sizeof(CircularList));
  return pReturn;
}

int getCircularListData(CircularList *pList, int position)
{
  CircularListNode *pCurrentNode = &(pList->headerNode);
  for (int i = 0; i <= position; i++)
  {
    pCurrentNode = pCurrentNode->pLink;
  }
  return pCurrentNode->data;
}

int addCircularListData(CircularList *pList, int position, int data)
{
  CircularListNode *pNewNode = NULL;
  CircularListNode *pPreNode = NULL;

  pNewNode = (CircularListNode *)malloc(sizeof(CircularListNode));
  pNewNode->data = data;

  pPreNode = &(pList->headerNode);
  for (int i = 0; i < position; i++)
  {
    pPreNode = pPreNode->pLink;
  }

  pNewNode->pLink = pPreNode->pLink;
  pPreNode->pLink = pNewNode;

  pList->currentCount++;
  if (pNewNode->pLink == NULL)
  { // 제일 첫 번째 노드 생성시 자기자신을 가르킴
    pNewNode->pLink = pNewNode;
  }

  return 0;
}

int removeCircularListData(CircularList *pList, int position)
{
  CircularListNode *pDelNode = NULL;
  CircularListNode *pPreNode = NULL;

  pPreNode = &(pList->headerNode);
  for (int i = 0; i < position; i++)
  {
    pPreNode = pPreNode->pLink;
  }

  pDelNode = pPreNode->pLink;
  pPreNode->pLink = pDelNode->pLink;

  pList->currentCount--;
  if (pList->currentCount == 0)
  {
    pList->headerNode.pLink = NULL;
  }
  free(pDelNode);
  return 0;
}

void deleteCircularList(CircularList *pList)
{
  CircularListNode *pDelNode = NULL;
  CircularListNode *pPreNode = pList->headerNode.pLink;
  for (int i = 0; i < pList->currentCount; i++)
  {
    pDelNode = pPreNode;
    pPreNode = pPreNode->pLink;
    free(pDelNode);
  }
  free(pList);
}

void displayCircularList(CircularList *pList)
{
  CircularListNode *pNode = NULL;
  pNode = pList->headerNode.pLink;
  if (pList->currentCount == 0)
  {
    printf("자료가 없습니다.");
  }
  else
  {
    printf("노드 개수 : %d\n", pList->currentCount);
    for (int i = 0; i < pList->currentCount; i++)
    {
      printf("[%d], %d\n", i, pNode->data);
      pNode = pNode->pLink;
    }
  }
}

int main(int argc, char *argv[])
{
  CircularList *pList = NULL;
  pList = createCircluarList();

  addCircularListData(pList, 0, 10);
  displayCircularList(pList);
  addCircularListData(pList, 0, 20);
  displayCircularList(pList);
  addCircularListData(pList, 1, 30);
  displayCircularList(pList);

  removeCircularListData(pList, 2);
  displayCircularList(pList);
  removeCircularListData(pList, 1);
  displayCircularList(pList);
  removeCircularListData(pList, 0);
  displayCircularList(pList);

  deleteCircularList(pList);

  return 0;
}
