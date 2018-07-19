#ifndef _LINKEDQUEUE_
#define _LINKEDQUEUE_

typedef struct LinkedQueueNodeType {
    int data;
    struct LinkedQueueNodeType* pLink;
} LinkedQueueNode;

typedef struct LinkedQueueType {
    int currentCount;            // 현재 노드 개수
    LinkedQueueNode* pFront;     // Front 노드의 포인터
    LinkedQueueNode* pRear;      // Rear 노드의 포인터
} LinkedQueue;

LinkedQueue* createLinkedQueue(); 
int isLinekdQueueEmpty(LinkedQueue* pQueue); 
int enqueueLQ(LinkedQueue* pQueue, char data);
LinkedQueueNode* dequeueLQ(LinkedQueue* pQueue);
LinkedQueueNode* peekLQ(LinkedQueue* pQueue);
void deleteLinkedQueue(LinkedQueue* pQueue);
void displayLinkedQueue(LinkedQueue* pQueue);

#endif