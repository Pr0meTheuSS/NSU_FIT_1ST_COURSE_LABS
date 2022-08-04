// "Copyright 2022 <Olimpiev Y.>"
#include "Queue.h"

TQueueNode* InitQueueNode(TCodeTreePtr* content) {
  assert(content);
  assert(sizeof(*content) == sizeof(TCodeTreePtr));
  TQueueNode* newNode = (TQueueNode*)calloc(1, sizeof(TQueueNode));
  assert(newNode);

  memcpy(&newNode->Content, content, sizeof(TCodeTreePtr));
  return newNode;
}

int EnQueue(TQueue* q, TCodeTreePtr* content) {
  assert(q);
  TQueueNode* newNode = InitQueueNode(content);
  assert(newNode);
  if (!q->Head) {
      q->Head = q->End = newNode;
      return EXIT_SUCCESS;
  }
  q->End->Next = newNode;
  q->End = newNode;
  return EXIT_SUCCESS;
}

int DeQueue(TQueue* q, TCodeTreePtr* content) {
  assert(q);
  if (!q->Head) {
      return EXIT_FAILURE;
  }
  TQueueNode* toDel = q->Head;
  memcpy(content, &q->Head->Content, sizeof(TCodeTreePtr));
  q->Head = q->Head->Next;
  free(toDel);
  return EXIT_SUCCESS;
}
