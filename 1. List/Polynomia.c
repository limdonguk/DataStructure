#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TermType {
	double coef;
	int degree;
} Term;

typedef struct LinkedListNodeType {
	Term data;
	struct LinkedListNodeType* pLink;
} LinkedListNode;

typedef struct LinkedListType {
	int currentNode;
	LinkedListNode headerNode;
} LinkedList, PolyList;

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

Term getLinkedListData(LinkedList* pList, int position) {
	LinkedListNode* pNode = &(pList->headerNode);
	for (int i = 0; i<position; i++) {
		pNode = pNode->pLink;
	}
	return pNode->data;
}

int addLinkedListData(LinkedList* pList, int position, Term data) {
	int ret = 0;
	
	LinkedListNode *pPreNode = NULL;
	LinkedListNode *pNewNode = NULL;

	pNewNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	pNewNode->data = data;

	pPreNode = &(pList->headerNode);
	for (int i = 0; i<position; i++) {
		pPreNode = pPreNode->pLink;
	}

	pNewNode->pLink = pPreNode->pLink;
	pPreNode->pLink = pNewNode;
	pList->currentNode++;

	return ret;
}

int removeLinkedListData(LinkedList *pList, int position) {
	int ret = 0;

	LinkedListNode *pDelNode = NULL;
	LinkedListNode *pPreNode = NULL;

	pPreNode = &(pList->headerNode);
	for (int i = 0; i<position; i++) {
		pPreNode = pPreNode->pLink;
	}

	pDelNode = pPreNode->pLink;
	pPreNode->pLink = pDelNode->pLink;
	free(pDelNode);
	pList->currentNode--;

	return ret;
}

int deleteLinkedList(LinkedList *pList) {
	LinkedListNode *pDelNode = NULL;
	LinkedListNode *pPreNode = pList->headerNode.pLink;

	while (pPreNode != NULL) {
		pDelNode = pPreNode;
		free(pDelNode);
		pPreNode = pPreNode->pLink;
	}
	free(pList);
}

// Find Last Node and Add New Data
int addPolyNodeLast(PolyList *pList, double coef, int degree) {
	int ret = 0;
	int position = 0;

	Term term = {0, };
	term.coef = coef;
	term.degree = degree;

	if (pList != NULL) {
		position = pList->currentNode;
		ret = addLinkedListData(pList, position, term);
	}

	return ret;
}

// Display Polynomias
void displayPolyList(PolyList *pList) {
	LinkedListNode *pNode = NULL;

	pNode = pList->headerNode.pLink;
	if (pList->currentNode == 0) {
		printf("입력 자료 없음");
	}
	for (int i = 0; i<pList->currentNode; i++) {
		if (i>0) {
			printf("+");
		}
		printf("%.1fx^%d", pNode->data.coef, pNode->data.degree);
		pNode = pNode->pLink;
	}
	printf("\n");
}

PolyList* polyAdd(PolyList* pListA, PolyList* pListB) {
	PolyList *pReturn = NULL;
	LinkedListNode *pNodeA = NULL;
	LinkedListNode *pNodeB = NULL;
	double coefSum = 0;

	if (pListA != NULL && pListB != NULL) {
		pReturn = createLinkedList();
		if (pReturn == NULL) {
			printf("메모리 할당 오류\n");
			return NULL;
		}

		pNodeA = pListA->headerNode.pLink;
		pNodeB = pListB->headerNode.pLink;
		while (pNodeA != NULL && pNodeB != NULL) {
			int degreeA = pNodeA->data.degree;
			int degreeB = pNodeB->data.degree;
			if (degreeA > degreeB) {
				coefSum = pNodeA->data.coef;
				addPolyNodeLast(pReturn, coefSum, degreeA);
				pNodeA = pNodeA->pLink;
			}
			else if (degreeA == degreeB) {
				coefSum = pNodeA->data.coef + pNodeB->data.coef;
				addPolyNodeLast(pReturn, coefSum, degreeA);
				pNodeA = pNodeA->pLink;
				pNodeB = pNodeB->pLink;
			}
			else {
				coefSum = pNodeB->data.coef;
				addPolyNodeLast(pReturn, coefSum, degreeB);
				pNodeB = pNodeB->pLink;
			}
		}

		while (pNodeA != NULL) {
			coefSum = pNodeA->data.coef;
			addPolyNodeLast(pReturn, coefSum, pNodeA->data.degree);
			pNodeA = pNodeA->pLink;
		}

		while (pNodeB != NULL) {
			coefSum = pNodeB->data.coef;
			addPolyNodeLast(pReturn, coefSum, pNodeB->data.degree);
			pNodeB = pNodeB->pLink;
		}
	}
	else {
		printf("오류, NULL 리스트\n");
	}

	return pReturn;
}

int main(int argc, char* argv[]) {
	PolyList *pListA = NULL;
	PolyList *pListB = NULL;
	PolyList *pListC = NULL;

	pListA = createLinkedList();
	pListB = createLinkedList();

	if (pListA != NULL && pListB != NULL) {
		// pListA : 7x^6 + 3x^5 + 5x^2
		// pListB : 1x^5 + 2x^4 + 3x^2 + 4x^0
		addPolyNodeLast(pListA, 7, 6);
		addPolyNodeLast(pListA, 3, 5);
		addPolyNodeLast(pListA, 5, 2);
		displayPolyList(pListA);

		addPolyNodeLast(pListB, 1, 5);
		addPolyNodeLast(pListB, 2, 4);
		addPolyNodeLast(pListB, 3, 2);
		addPolyNodeLast(pListB, 4, 0);
		displayPolyList(pListB);

		pListC = polyAdd(pListA, pListB);
		if (pListC != NULL) {
			displayPolyList(pListC);
			deleteLinkedList(pListC);
		}

		deleteLinkedList(pListA);
		deleteLinkedList(pListB);
	}

	return 0;
}




