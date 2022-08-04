// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "CodeTree.h"

typedef struct TCodeTree* TCodeTreePtr;
typedef struct TQueueNode TQueueNode;
typedef struct TQueue TQueue;

struct TQueueNode {
  TQueueNode* Next;
  TCodeTreePtr Content;
};

struct TQueue {
  TQueueNode* Head;
  TQueueNode* End;
};

TQueueNode* InitQueueNode(TCodeTreePtr* content);

int EnQueue(TQueue* q, TCodeTreePtr* content);

int DeQueue(TQueue* q, TCodeTreePtr* content);
