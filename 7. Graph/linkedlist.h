#ifndef _LINKEDLIST_
#define _LINKEDLIST_

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

LinkedList *createLinkedList();
int getLinkedListData(LinkedList *pList, int position);
int addLinkedListData(LinkedList *pList, int position, int data);
int removeLinkedListData(LinkedList *pList, int position);
void deleteLinkedList(LinkedList *pList);
int getLinkedListLength(LinkedList *pList);

#endif
