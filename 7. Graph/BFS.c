#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraygraph.h"
#include "linkedqueue.h"

void traversalBFS(ArrayGraph* pGraph, int startNodeID){
    int i = 0;
    int nodeID = 0;
    LinkedQueue* pQueue = NULL;
    LinkedQueueNode* pQueueNode = NULL;
    int *pVisit = NULL;

    if(pGraph == NULL) {
        return;
    }
    pQueue = createLinkedQueue();
    pVisit = malloc(sizeof(int)*pGraph->nodeCount);
    if(pQueue == NULL && pVisit == NULL) {
        return;
    }
    memset(pVisit, 0, sizeof(int) * pGraph->nodeCount);
    pVisit[startNodeID] = 1;
    enqueueLQ(pQueue, startNodeID);

    while(isLinekdQueueEmpty(pQueue) == 0) {
        pQueueNode = dequeueLQ(pQueue);
        if(pQueueNode != NULL) {
            nodeID = pQueueNode->data;
            printf("노드-[%d] 방문\n",nodeID);
            for(i = 0; i<pGraph->nodeCount; i++) {
                if(i != nodeID) {
                    if(getEdgeDAG(pGraph, nodeID, i) != 0) {
                        if(pVisit[i] == 0) {
                            pVisit[i] = 1;
                            enqueueLQ(pQueue, i);
                        }
                    }
                }
            }
            free(pQueueNode);
        }
    }
    deleteLinkedQueue(pQueue);
    free(pVisit);
}