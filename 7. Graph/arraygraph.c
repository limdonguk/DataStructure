#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraygraph.h"

ArrayGraph* createDirectArrayGraph(int graphType, int nodeCount) {
    int i=0;
    ArrayGraph *pReturn = NULL;

    pReturn = (ArrayGraph*)malloc(sizeof(ArrayGraph));
    if(pReturn == NULL) {
        return NULL;
    }

    pReturn->graphType = graphType;
    pReturn->nodeCount = nodeCount;
    pReturn->ppEdge = (int **)malloc(sizeof(int *) * nodeCount);
    if(pReturn->ppEdge == NULL) {
        return NULL;
    }

    for(i = 0; i < nodeCount; i++) {
        pReturn->ppEdge[i] = (int *)malloc(sizeof(int) * nodeCount);
        if(pReturn->ppEdge[i] == NULL) {
            return NULL;
        }
        memset(pReturn->ppEdge[i], 0, sizeof(int *) * nodeCount);
    }
    return pReturn;
}

int checkVertexValid(ArrayGraph *pGraph, int node) {
    if(pGraph != NULL && node < pGraph->nodeCount && node>=0) {
        return 1;
    }
    else {
        return 0;
    }
}

int addEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    if(pGraph != NULL
       && checkVertexValid(pGraph, fromNode)
       && checkVertexValid(pGraph, toNode)) {
           pGraph->ppEdge[fromNode][toNode] = 1;
    }
    else {
        ret = 1;
    }  
    return ret;
}

int addEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode){
    int ret = 0;  
    ret = addEdgeInternalAG(pGraph, fromNode, toNode);
    if(ret == 0 && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = addEdgeInternalAG(pGraph, toNode, fromNode);
    }
    return ret;
}

int removeEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;
    if(pGraph != NULL
       && checkVertexValid(pGraph, fromNode)
       && checkVertexValid(pGraph, toNode)) {
           pGraph->ppEdge[fromNode][toNode] = 0;
    }
    else {
        ret = -1;
    }  
    return ret;
}

int removeEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode) {
    int ret = 0;  
    ret = removeEdgeInternalAG(pGraph, fromNode, toNode);
    if(ret == 0 && ARRAY_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = removeEdgeInternalAG(pGraph, toNode, fromNode);
    }
    return ret;
}

int getEdgeDAG(ArrayGraph* pGraph, int fromNode, int toNode) {
    int ret = 0;

    if(pGraph != NULL
       && checkVertexValid(pGraph, fromNode)
       && checkVertexValid(pGraph, toNode)) {
           ret = pGraph->ppEdge[fromNode][toNode];
    }
    return ret;
}

void displayGraphDAG(ArrayGraph* pGraph) {
    int i = 0, j = 0;
    int count = 0;

    if(pGraph != NULL) {
        count = pGraph->nodeCount;
        for(i = 0; i<count; i++) {
            for(j = 0; j<count; j++) {
                printf("%d ",getEdgeDAG(pGraph, i, j));
            }
            printf("\n");
        }
    }
}

void deleteGraphDAG(ArrayGraph *pGraph){
    int i=0;

    if(pGraph != NULL) {
        for(i = 0; i<pGraph->nodeCount; i++) {
            free(pGraph->ppEdge[i]);
        }
        free(pGraph->ppEdge);
        free(pGraph);
    }
}

void traversalDFS(ArrayGraph* pGraph, int startNodeID, int *pVisit) {
    int i = 0;
    pVisit[startNodeID] = 1;
    printf("노드-[%d] 방문\n",startNodeID);
    for(i=0; i<pGraph->nodeCount; i++) {
        if(i != startNodeID) {
            if(getEdgeDAG(pGraph, startNodeID, i) != 0) {
                if(pVisit[i] == 0) {
                    traversalDFS(pGraph, i, pVisit);
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int nodeCount = 4;
    int graphType = ARRAY_GRAPH_TYPE_UNDIRECT;
    int *pVisit = malloc(sizeof(int)*nodeCount);

    ArrayGraph *pG1 = createDirectArrayGraph(graphType, nodeCount);
    if(pG1 != NULL && pVisit != NULL) {
        addEdgeDAG(pG1, 0, 1);
        addEdgeDAG(pG1, 1, 2);
        addEdgeDAG(pG1, 2, 0);
        memset(pVisit, 0, sizeof(int) * nodeCount);
        printf("pG1 : DFS\n");
        traversalDFS(pG1, 0, pVisit);
        deleteGraphDAG(pG1);
        free(pVisit);
    }
    return 0;
}
