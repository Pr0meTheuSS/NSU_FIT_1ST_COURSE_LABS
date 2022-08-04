// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "CodeTree.h"

typedef size_t HeapKeyType;
typedef struct THeapElement THeapElement;
typedef struct THeap THeap;
typedef struct TCodeTree* TContent;

struct THeapElement {
    TContent Content;
    HeapKeyType Key;
};

struct THeap {
    THeapElement* Elements;
    size_t Size;
    size_t EndIndex;
};

void Swap(THeapElement* left, THeapElement* right);

THeap* InitHeap(size_t heap_size);

int AddToHeap(THeap* heap,
              TContent* content,
              HeapKeyType key);

void Heapify(THeap* heap);

int GetRoot(THeap* heap, TContent* content);

void FreeHeap(THeap* heap);
