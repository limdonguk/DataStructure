#ifndef _ARRAYGRAPH_
#define _ARRAYGRAPH_

#define ARRAY_GRAPH_TYPE_DIRECT      0
#define ARRAY_GRAPH_TYPE_UNDIRECT    1

typedef struct ArrayGraphType {
    int graphType;
    int nodeCount;
    int **ppEdge;
} ArrayGraph;

ArrayGraph* createDirectArrayGraph(int graphType, int nodeCount);
int checkVertexValid(ArrayGraph *pGraph, int node);
int addEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode);
int addEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode);
int removeEdgeInternalAG(ArrayGraph *pGraph, int fromNode, int toNode);
int removeEdgeDAG(ArrayGraph *pGraph, int fromNode, int toNode);
int getEdgeDAG(ArrayGraph* pGraph, int fromNode, int toNode);
void displayGraphDAG(ArrayGraph* pGraph);
void deleteGraphDAG(ArrayGraph *pGraph);
void traversalDFS(ArrayGraph* pGraph, int startNodeID, int *pVisit);

#endif