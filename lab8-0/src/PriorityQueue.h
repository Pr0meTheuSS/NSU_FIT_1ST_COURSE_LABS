// "Copyright [2022] <Olimpiev Y.>"
#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>  // for memcpy()
#include "Service.h"
#include "Graph.h"


struct TPriorityQueueNode {
  struct TPriorityQueueNode* Next;
  TEdge Content;
  TEdgeWeightType Priority;
};

struct TPriorityQueue {
  struct TPriorityQueueNode* Head;
};


TPriorityQueueNode* InitPriorityQueueNode(TEdge content, TEdgeWeightType priority);

int EnQueue(TPriorityQueue* q, TEdge content, TEdgeWeightType priority);

int DeQueue(TPriorityQueue* q, TEdge* content);

void FilterQueue(TPriorityQueue* q, TNodeIndexType limit);

TPriorityQueue GetAllUnvisitedIncedenceEdges(TGraph graph, TNodeIndexType start);
