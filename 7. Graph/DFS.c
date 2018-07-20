#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraygraph.h"

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