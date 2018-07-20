#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedqueue.h"

LinkedQueue* createLinkedQueue() {
    LinkedQueue* pReturn = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    memset(pReturn, 0, sizeof(LinkedQueue));
    return pReturn;
}

int isLinekdQueueEmpty(LinkedQueue* pQueue) {
    int ret = 0;
    if(pQueue != NULL) {
        if(pQueue->currentCount == 0) {
            ret = 1;
        }
    }
    return ret;
}

int enqueueLQ(LinkedQueue* pQueue, char data) {
    int ret = 0;
    LinkedQueueNode* pNode = NULL;

    pNode = (LinkedQueueNode*)malloc(sizeof(LinkedQueueNode)); // 새로운 노드 생성
    pNode->data = data;                                        // 노드 초기화
    pNode->pLink = NULL;                                       // 노드 초기화

    // 큐가 비어있지 않을 경우
    if(isLinekdQueueEmpty(pQueue) == 0) {
        pQueue->pRear->pLink = pNode;                          // 기존 리어 노드의 다음 노드 지정
        pQueue->pRear = pNode;                                 // 큐 자체의 리어 노드 링크 변경
    }
    //큐가 비어있을 경우
    else {
        pQueue->pFront = pNode;
        pQueue->pRear = pNode;
    }

    pQueue->currentCount++;
    ret = 1;

    return ret;
}

LinkedQueueNode* dequeueLQ(LinkedQueue* pQueue) {
    LinkedQueueNode* pReturn = NULL;

    // 큐가 비어있지 않을 경우
    if(isLinekdQueueEmpty(pQueue) == 0) {
        pReturn = pQueue->pFront;
        pQueue->pFront = pQueue->pFront->pLink;
        pReturn->pLink = NULL;

        pQueue->currentCount--;
        
        // dequeue한 노드가 마지막 노드일 경우 rear에 대한 처리
        // pRear와 pFront가 같은 노드를 가르키는 경우
        if(isLinekdQueueEmpty(pQueue) == 1) {
            pQueue->pRear = NULL;
        }
    }
    return pReturn;
}

LinkedQueueNode* peekLQ(LinkedQueue* pQueue) {
    LinkedQueueNode* pReturn = NULL;
    if(pQueue != NULL) {
        if(isLinekdQueueEmpty(pQueue) == 0) {
            pReturn = pQueue->pFront;
        }
    }
    return pReturn;
}

void deleteLinkedQueue(LinkedQueue* pQueue) {
    LinkedQueueNode* pNode = NULL;
    LinkedQueueNode* pDelNode = NULL;

    if(pQueue != NULL) {
        pNode = pQueue->pFront;
        while(pNode != NULL) {
            pDelNode = pNode;
            pNode = pNode->pLink;
            free(pDelNode);
        }
        free(pQueue);
    }
}

void displayLinkedQueue(LinkedQueue* pQueue) {
    int i=0;
    LinkedQueueNode* pNode = NULL;

    if(pQueue != NULL) {
        printf("현재 노드 개수 : %d, ",pQueue->currentCount);

        pNode = pQueue->pFront;
        while(pNode != NULL) {
            printf("[%d]-[%c]\n",i, pNode->data);
            i++;
            pNode = pNode->pLink;
        }
    }
}