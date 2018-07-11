#include <stdio.h>
#include <stdlib.h>

typedef struct ArrayQueueNodeType {
    char data;
} ArrayQueueNode;

typedef struct ArrayQueueType {
    int maxCount;          // 최대 자료 개수
    int currentCount;      // 현재 자료 개수
    int front;             // 프런트 위치
    int rear;              // 리어 위치
    ArrayQueueNode *pData; // 자료를 저장하는 1차원 배열 포인터
} ArrayQueue;

ArrayQueue* createArrayQueue(int size) {
    ArrayQueue *pReturn = NULL;                     // 17 - 24 : 배열 선형 큐 자체의 메모리 할당
    pReturn = (ArrayQueue *)malloc(sizeof(ArrayQueue)*size);
    memset(pReturn, 0, sizeof(ArrayQueue)*size);    // 구조체의 멤버변수들을 모두 0으로 초기화

    pReturn->maxCount = size;
    pReturn->currentCount = 0;
    pReturn->front = -1;
    pReturn->rear = -1;

    pReturn->pData = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode)*size); // 실제 자료를 저장할 배열 자체를 생성
    memset(pReturn->pData, 0, sizeof(ArrayQueueNode)*size);                 // 배열을 0으로 초기화

    return pReturn;
}

int isArrayQueueFull(ArrayQueue* pQueue) {
    int ret = 0;

    if(pQueue != NULL) {
        if(pQueue->currentCount == pQueue->maxCount) {
            ret = 1;
        }
    }
    return ret;
}

int enqueueAQ(ArrayQueue* pQueue, char data) {
    int ret = 0;

    if(pQueue != NULL) {
        if(isArrayQueueFull(pQueue) == 0) {
            pQueue->rear++;                            // rear 한 칸 이동
            pQueue->pData[pQueue->rear].data = data;   // 새로운 자료 추가
            pQueue->currentCount++;                    // 현재 자료 개수 증가
            ret = 1;
        }
        else {
            printf("오류, 큐가 가득 참\n");
        }
    }
    return ret;
}

int isArrayQueueEmpty(ArrayQueue* pQueue) {
    int ret = 0;

    if(pQueue != NULL) {
        if(pQueue->currentCount == 0) {
            ret = 1;
        }
    }
    return ret;
}

ArrayQueueNode* dequeueAQ(ArrayQueue* pQueue) {
    ArrayQueueNode *pReturn = NULL;
    if(pQueue != NULL) {
        if(isArrayQueueEmpty(pQueue) == 0) {
            pReturn = (ArrayQueueNode *)malloc(sizeof(ArrayQueueNode));
            pQueue->front++;                                            // front 한 칸 이동
            pReturn->data = pQueue->pData[pQueue->front].data;          // pReturn의 data에 front가 가르키는 데이터 저장
            pQueue->currentCount--;                                     // 현재 노드 개수 1 감소
        }
        else {
            printf("오류, 메모리할당\n");
        }
    }
    return pReturn;
}

ArrayQueueNode* peekAQ(ArrayQueue *pQueue) {
    ArrayQueueNode *pReturn = NULL;
    if(pQueue != NULL) {
        if(isArrayQueueEmpty(pQueue) == 0) {
            pReturn = &(pQueue->pData[pQueue->front+1]);
        }
    }
    return pReturn;
}

void deleteArrayQueue(ArrayQueue *pQueue) {
    if(pQueue != NULL) {
        if(pQueue->pData != NULL) {
            free(pQueue->pData);
        }
        free(pQueue);
    }
}

void displayArrayQueue(ArrayQueue *pQueue){
    int i=0;
    if(pQueue != NULL) {
        printf("큐의 크기 : %d, 현재 노드 개수 : %d\n",pQueue->maxCount, pQueue->currentCount);
        for(i=pQueue->front+1; i<=pQueue->rear; i++) {
            printf("[%d]-[%c]\n", i, pQueue->pData[i].data);
        }
    }
}

int main(int argc, char* argv[]) {
    ArrayQueue *pQueue = NULL;
    ArrayQueueNode *pNode = NULL;

    pQueue = createArrayQueue(4);
    if(pQueue != NULL) {
        enqueueAQ(pQueue, 'A');
        enqueueAQ(pQueue, 'B');
        enqueueAQ(pQueue, 'C');
        enqueueAQ(pQueue, 'D');
        displayArrayQueue(pQueue);

        pNode = dequeueAQ(pQueue);
        if(pNode != NULL) {
            printf("Dequeue Value -[%c]\n",pNode->data);
            free(pNode);
        }
        displayArrayQueue(pQueue);

        pNode = peekAQ(pQueue);
        if(pNode != NULL) {
            printf("Peek Value -[%c]\n",pNode->data);
        }
        displayArrayQueue(pQueue);

        enqueueAQ(pQueue, 'E');
        displayArrayQueue(pQueue);
    }
    return 0;
}



