#include <stdio.h>
#include <stdlib.h>
#include "exprlinkedstack.h" 

LinkedStack *createLinkedStack()
{
	LinkedStack *pStack = NULL;
	pStack = (LinkedStack *)malloc(sizeof(LinkedStack));
	memset(pStack, 0, sizeof(LinkedStack));

	return pStack;
}

int pushLS(LinkedStack *pStack, ExprToken data)
{
	int ret = 0;
	LinkedStackNode *pNode = NULL;

	if (pStack != NULL)
	{
		pNode = (LinkedStackNode *)malloc(sizeof(LinkedStackNode));
		if (pNode != NULL)
		{
			pNode->data = data;
			pNode->pLink = pStack->pTop;
			pStack->pTop = pNode;

			pStack->currentCount++;
			ret = 1;
		}
		else
		{
			printf("메모리 할당 오류");
		}
	}
	else
	{
		printf("스택이 존재하지 않음");
	}
	return ret;
}

int isLinkedStackEmpty(LinkedStack *pStack)
{
	int ret = 0;

	if (pStack != NULL)
	{
		if (pStack->currentCount == 0)
		{
			ret = 1;
		}
	}
	return ret;
}

LinkedStackNode *popLS(LinkedStack *pStack)
{
	LinkedStackNode *pReturn = NULL;
	if (pStack != NULL)
	{
		if (isLinkedStackEmpty(pStack) == 0)
		{
			pReturn = pStack->pTop;
			pStack->pTop = pReturn->pLink;
			pReturn->pLink = NULL;

			pStack->currentCount--;
		}
	}

	return pReturn;
}

LinkedStackNode *peekLS(LinkedStack *pStack)
{
	LinkedStackNode *pReturn = NULL;
	if (pStack != NULL)
	{
		if (isLinkedStackEmpty(pStack) == 0)
		{
			pReturn = pStack->pTop;
		}
	}
	return pReturn;
}

void deleteLinkedStack(LinkedStack *pStack)
{
	LinkedStackNode *pNode = NULL;
	LinkedStackNode *pDelNode = NULL;

	if (pStack != NULL)
	{
		pNode = pStack->pTop;
		while (pNode != NULL)
		{
			pDelNode = pNode;
			pNode = pNode->pLink;
			free(pDelNode);
		}
		free(pStack);
	}
}

void displayLinkedStack(LinkedStack *pStack)
{
	LinkedStackNode *pNode = NULL;
	int i = 0;
	if (pStack != NULL)
	{
		printf("현재 노드 개수 : %d\n", pStack->currentCount);
		pNode = pStack->pTop;
		while (pNode != NULL)
		{
			printf("[%d]-[%c]\n", pStack->currentCount - 1, pNode->data);
			i++;
			pNode = pNode->pLink;
		}
	}
}