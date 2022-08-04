// "Copyright 2022 <Olimpiev Y.>"
#include "Heap.h"

void Swap(THeapElement* left, THeapElement* right) {
  THeapElement temp = *left;
  *left = *right;
  *right = temp;
}

THeap* InitHeap(size_t heap_size) {
  THeap* heap = (THeap*)calloc(1, sizeof(THeap));
  assert(heap);
  heap->Size = heap_size;
  heap->Elements = (THeapElement*)calloc(heap->Size, sizeof(THeapElement));
  assert(heap->Elements);
  return heap;
}

void Heapify(THeap* heap) {
  size_t curr = 0;
  size_t left = 2 * curr + 1;
  size_t right = 2 * curr + 2;
  size_t newRoot = 0;

  while (curr < heap->EndIndex) {
    if (left < heap->EndIndex &&
        heap->Elements[left].Key < heap->Elements[newRoot].Key) {
      newRoot = left;
    }
    if (right < heap->EndIndex &&
        heap->Elements[right].Key < heap->Elements[newRoot].Key) {
      newRoot = right;
    }
    if (newRoot == curr) {
      break;
    }
    Swap(&heap->Elements[curr], &heap->Elements[newRoot]);
    curr = newRoot;
    left = 2 * curr + 1;
    right = 2 * curr + 2;
  }
}

int AddToHeap(THeap* heap,
  TContent* content,
  HeapKeyType key) {
  assert(heap);
  if (heap->EndIndex >= heap->Size) {
    return EXIT_FAILURE;
  }
  memcpy(&heap->Elements[heap->EndIndex].Content, content, sizeof(TContent));
  heap->Elements[heap->EndIndex].Key = key;

  Heapify(heap);
  heap->EndIndex++;
  return EXIT_SUCCESS;
}

int GetRoot(THeap* heap, TContent* content) {
  assert(heap);
  assert(content);
  assert(heap->Size);

  if (heap->EndIndex < 1) {
    return EXIT_FAILURE;
  }
  memcpy(content, &heap->Elements[0].Content, sizeof(TContent));

  Swap(&heap->Elements[0], &heap->Elements[heap->EndIndex - 1]);

  heap->EndIndex--;
  Heapify(heap);
  return EXIT_SUCCESS;
}

void FreeHeap(THeap* heap) {
  if (heap) {
    free(heap->Elements);
    heap->EndIndex = heap->Size = 0;
    free(heap);
  }
}
