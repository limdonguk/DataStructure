#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define ARRAY_GRAPH_TYPE_DIRECT      0
#define ARRAY_GRAPH_TYPE_UNDIRECT    1

typedef struct LinkedListGraphType {
    int graphType;
    int nodeCount;
    LinkedList** ppAdjEdge;
} LinkedGraph;

LinkedGraph* createDirectLinkedGraph(int graphType, int nodeCount) {
    int i = 0;
    LinkedGraph *pReturn = NULL;

    if(nodeCount > 0) {
        pReturn = (LinkedGraph*)malloc(sizeof(LinkedGraph));
        if(pReturn == NULL) {
            printf("error\n");
            return NULL;
        }
        pReturn->graphType = graphType;
        pReturn->nodeCount = nodeCount;
    }
    else {
        printf("error\n");
        return NULL;
    }
    pReturn->ppAdjEdge = (LinkedList**)malloc(sizeof(LinkedList*) * nodeCount);
    if(pReturn->ppAdjEdge == NULL) {
        printf("error\n");
        if(pReturn != NULL) free(pReturn);
        return NULL;
    }
    for(i = 0; i<nodeCount; i++) {
        pReturn->ppAdjEdge[i] = createLinkedList();
        if(pReturn->ppAdjEdge[i] == NULL) {
            printf("error\n");
            if(pReturn->ppAdjEdge != NULL) free(pReturn->ppAdjEdge);
            if(pReturn != NULL) free(pReturn);
            return NULL;
        }
    }
    return pReturn;
}

int checkVertexValid(LinkedGraph *pGraph, int node) {
    if(pGraph != NULL && node < pGraph->nodeCount && node>=0) {
        return 1;
    }
    else {
        return 0;
    }
}

int addEdgeInternalDLG(LinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
     if(pGraph != NULL
       && checkVertexValid(pGraph, fromNode)
       && checkVertexValid(pGraph, toNode))
    {
        addLinkedListData(pGraph->ppAdjEdge[fromNode], 0, toNode);
    } 
    else {
        ret = 1;
    }
    return ret;
}

int addEdgeDLG(LinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    
    ret = addEdgeInternalDLG(pGraph, fromNode, toNode);
    if(pGraph != NULL && pGraph->graphType == ARRAY_GRAPH_TYPE_UNDIRECT) {
        ret = addEdgeInternalDLG(pGraph, toNode, fromNode);
    }

    return ret;
}

int removeEdgeInternalDLG(LinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    LinkedList *pFromList = NULL;
    LinkedList *pToList = NULL;
    int i = 0, count = 0;

    if(pGraph != NULL
       && checkVertexValid(pGraph, fromNode)
       && checkVertexValid(pGraph, toNode))
    {
        pFromList = pGraph->ppAdjEdge[fromNode];
        pToList = pGraph->ppAdjEdge[toNode];
        count = getLinkedListLength(pFromList);
        for(i = 0; i<count; i++) {
            if(getLinkedListData(pFromList, i) == toNode) {
                removeLinkedListData(pFromList, i);
                ret = 0;
            }
            if(getLinkedListData(pToList, i) == fromNode) {
                removeLinkedListData(pToList, i);
                ret = 0;
            }
        }
    }
    else {
        ret = -1;
    }
}

int removeEdgeDLG(LinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    
    ret = removeEdgeInternalDLG(pGraph, fromNode, toNode);
    if(pGraph != NULL && pGraph->graphType == ARRAY_GRAPH_TYPE_UNDIRECT) {
        ret = removeEdgeInternalDLG(pGraph, toNode, fromNode);
    }

    return ret;
}

int getEdgeLDG(LinkedGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    LinkedList *pList = NULL;
    int i = 0, count = 0;

    if(pGraph != NULL
       && checkVertexValid(pGraph, fromNode)
       && checkVertexValid(pGraph, toNode)) {
           pList = pGraph->ppAdjEdge[fromNode];
           count = getLinkedListLength(pList);
           for(i = 0; i<count; i++) {
               if(getLinkedListData(pList, i) == toNode) {
                   ret = 1;
                   break;
               }
           }
    }
    return ret;
}

void displayGraphDLG(LinkedGraph *pGraph) {
    int i = 0, j = 0, count = 0;

    if(pGraph != NULL) {
        count = pGraph->nodeCount;
        for(i=0; i<count; i++) {
            for(j=0; j<count; j++) {
                if(getEdgeLDG(pGraph, i, j)) {
                    printf("1 ");
                }
                else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
}

void deleteGraphDLG(LinkedGraph *pGraph) {
    int i = 0;

    if(pGraph != NULL) {
        for(i = 0; i<pGraph->nodeCount; i++) {
            deleteLinkedList(pGraph->ppAdjEdge[i]);
        }
        if(pGraph->ppAdjEdge != NULL) free(pGraph->ppAdjEdge);
        free(pGraph);
    }
}

int main(int argc, char* argv[]) {
    int nodeCount = 0;
    int graphType = ARRAY_GRAPH_TYPE_UNDIRECT;

    LinkedGraph *pG2 = createDirectLinkedGraph(graphType, nodeCount);
    if(pG2 != NULL) {
        addEdgeDLG(pG2, 0, 1);
        addEdgeDLG(pG2, 1, 2);
        addEdgeDLG(pG2, 2, 0);
        addEdgeDLG(pG2, 2, 3);
        addEdgeDLG(pG2, 3, 2);
        addEdgeDLG(pG2, 3, 4);
        addEdgeDLG(pG2, 4, 5);
        addEdgeDLG(pG2, 5, 3);

        printf("G2 : 무방향 그래프\n");
        displayGraphDLG(pG2);

        deleteGraphDLG(pG2);
    }
    return 0;
}