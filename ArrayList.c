#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArrayListNodeType {
	int data; // 데이터 저장
} ArrayListNode;

// if(currentCount <= maxCount)
typedef struct ArrayListType {
	int maxCount; // 최대 자료 개수
	int currentCount; // 현재 자료 개수
	ArrayListNode *pData; // 자료 저장을 위한 1차원 배열
} ArrayList;

// createList() : 리스트 생성
ArrayList *createList(int count) {
	ArrayList *pReturn = NULL;
	if (count > 0) {
		pReturn = (ArrayList*)malloc(sizeof(ArrayList));
		if (pReturn != NULL) {
			pReturn->maxCount = count;
			pReturn->currentCount = 0;
			pReturn->pData = NULL;
		}
		else {
			printf("오류, 메모리할당 실패\n");
			return NULL;
		}
	}
	else {
		printf("오류, 최대 원소 개수는 0개 이상이어야 합니다.\n");
		return NULL;
	}
	pReturn->pData = (ArrayListNode*)malloc(sizeof(ArrayListNode)*count);
	if (pReturn->pData == NULL) {
		printf("오류, 2번째 메모리 할당\n");
		free(pReturn);
		return NULL;
	}
	memset(pReturn->pData, 0, sizeof(ArrayListNode)*count);

	return pReturn;
}
// addListData() : 값 입력
int addListData(ArrayList* pList, int position, int data) {
	int i = 0;
	int errorCode = 0;
	if (pList != NULL) {
		if (pList->currentCount < pList->maxCount) {
			if (position >= 0 && position <= pList->currentCount) {
				//추가되는 위치와 그 오른쪽에 있는 기존 자료를 모두 오른쪽으로 한칸씩 이동.
				for (i = pList->currentCount - 1; i >= position; i--) { // 
					pList->pData[i + 1] = pList->pData[i];
				}
				pList->pData[position].data = data; // 실제 자료 추가
				pList->currentCount++; // 현재 저장된 자료 개수를 1개씩 증가.
			}
			else {
				printf("오류, 위치 인덱스 범위 초과 addListData\n");
				errorCode = 2;
			}
		}
		else {
			printf("오류, 리스트 용량 초과 addListData\n");
			errorCode = 2;
		}
	}
	else {
		printf("오류, List가 NULL 입니다.addListData");
		errorCode = 1;
	}

	return errorCode;
}

// removeListData() : 값 제거
int removeListData(ArrayList *pList, int position) {
	int i = 0;
	int errorCode = 0;
	if (pList != NULL) {
		if (position >= 0 && position < pList->currentCount) {
			for (i = position; i < pList->currentCount - 1; i++) {
				pList->pData[i] = pList->pData[i + 1];
			}
			pList->currentCount--;
		}
		else {
			printf("오류, 위치 인덱스 범위 초과 removeListData\n");
			errorCode = 2;
		}
	}
	else {
		printf("오류, List가 NULL 입니다. removeListData");
		errorCode = 1;
	}

	return errorCode;
}

// getListData() : 값 가져오기
int getListData(ArrayList* pList, int position) {
	int errorCode = 0;
	if (pList != NULL) {
		if (position > 0 && position < pList->currentCount) {
			return pList->pData[position].data;
		}
		else {
			printf("오류, 위치 인덱스 범위 초과 getListData\n");
			errorCode = 2;
		}
	}
	else {
		printf("오류, List가 NULL 입니다. getListData");
		errorCode = 1;
	}
	return errorCode;
}

// deleteList() : 리스트 삭제
void deleteList(ArrayList* pList) {
	if (pList != NULL) {
		if (pList->pData != NULL) {
			free(pList->pData);
		}
		free(pList);
	}
}

int getListLength(ArrayList* pList) {
	return pList->currentCount;
}

int main(int argc, char* argv[]) {
	ArrayList *pList = NULL;
	int value = 0;
	int dataCount = 0;

	pList = createList(3);
	addListData(pList, 0, 10);
	addListData(pList, 1, 20);
	addListData(pList, 0, 30);

	value = getListData(pList, 1);
	dataCount = getListLength(pList);
	printf("위치 : %d, 값 : %d, 크기 : %d\n", 1, value, dataCount);

	removeListData(pList, 0);
	deleteList(pList);

	return 0;
}



