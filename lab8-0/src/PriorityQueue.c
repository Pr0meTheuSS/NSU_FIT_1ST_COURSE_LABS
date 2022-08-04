// "Copyright [2022] <Olimpiev Y.>"
#include "PriorityQueue.h"


TPriorityQueueNode* InitPriorityQueueNode(TEdge content, TEdgeWeightType priority) {
  TPriorityQueueNode* newNode = (TPriorityQueueNode*)calloc(1, sizeof(TPriorityQueueNode));
  assert(newNode);
  newNode->Priority = priority;
  memcpy(&newNode->Content, &content, sizeof(newNode->Content));
  return newNode;
}


int EnQueue(TPriorityQueue* q, TEdge content, TEdgeWeightType priority) {
  assert(q);
  TPriorityQueueNode* newNode = InitPriorityQueueNode(content, priority);
  if (!q->Head) {
    q->Head = newNode;
    return EXIT_SUCCESS;
  }
  if (priority < q->Head->Priority) {
    newNode->Next = q->Head;
    q->Head = newNode;
    return EXIT_SUCCESS;
  }
  TPriorityQueueNode* curr = q->Head;
  while (curr->Next && curr->Next->Priority < newNode->Priority) {
    curr = curr->Next;
  }
  newNode->Next = curr->Next;
  curr->Next = newNode;
  return EXIT_SUCCESS;
}


int DeQueue(TPriorityQueue* q, TEdge* content) {
  assert(q);
  if (!q->Head) {
    return EXIT_FAILURE;
  }
  TPriorityQueueNode* toDel = q->Head;
  memcpy(content, &q->Head->Content, sizeof(*content));
  q->Head = q->Head->Next;
  free(toDel);
  return EXIT_SUCCESS;
}


void FilterQueue(TPriorityQueue* q, TNodeIndexType limit) {
  assert(q);
  TPriorityQueueNode* currNode = q->Head;
  if (currNode) {
    while (limit && currNode->Next) {
      currNode = currNode->Next;
      limit--;
    }
    TPriorityQueueNode* overNode = NULL;
    if (currNode) {
      overNode = currNode->Next;
      currNode->Next = NULL;
    }
    while (overNode) {
      TPriorityQueueNode* toDel = overNode;
      overNode = overNode->Next;
      free(toDel);
    }
  }
}

TPriorityQueue GetAllUnvisitedIncedenceEdges(TGraph graph, TNodeIndexType start) {
  TPriorityQueue q = { NULL };
  q.Head = NULL;
  for (TNodeIndexType i = 0; i < graph.NodesAmount; i++) {
    if (PathExist(graph, start, i) && !WasVisited(graph, i)) {
      TEdge currEdge = { start, i, GetWeight(graph, start, i) };
      EnQueue(&q, currEdge, currEdge.Weight);
    }
  }
  return q;
}
