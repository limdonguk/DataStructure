#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedListNodeType
{
	double data;
	struct LinkedListNodeType *pLink;
} LinkedListNode;

typedef struct LinkedListType
{
	int currentCount;
	LinkedListNode headerNode;
} LinkedList;

LinkedList *createLinkedList()
{
	LinkedList *pReturn = (LinkedList *)malloc(sizeof(LinkedList));
	memset(pReturn, 0, sizeof(LinkedList));
	return pReturn;
}

void addLinkedListData(LinkedList *pList, double data)
{
	LinkedListNode *pPreNode = NULL;
	LinkedListNode *pNewNode = NULL;

	pPreNode = &(pList->headerNode);
	while (pPreNode->pLink != NULL)
	{
		pPreNode = pPreNode->pLink;
	}

	pNewNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	pNewNode->pLink = NULL;
	pNewNode->data = data;
	pPreNode->pLink = pNewNode;

	pList->currentCount++;
}

double sumLinkedListData(LinkedList *pList)
{
	double total = 0;
	LinkedListNode *pNode = NULL;

	pNode = &(pList->headerNode);
	for (int i = 0; i <= pList->currentCount; i++)
	{
		total += pNode->data;
		pNode = pNode->pLink;
	}

	return total / pList->currentCount;
}

int main(int argc, char *argv[])
{
	int i = 1;
	double inputData = 0;
	LinkedList *pList = NULL;

	pList = createLinkedList();

	while (1)
	{
		printf("> %d번째 점수는? (-1을 입력하면 끝납니다.) : ", i);
		scanf_s("%lf", &inputData);

		if (inputData == -1)
		{
			break;
		}
		else
		{
			addLinkedListData(pList, inputData);
			i++;
		}
	}

	printf("%d명의 평균 : %f\n", pList->currentCount, sumLinkedListData(pList));

	return 0;
}