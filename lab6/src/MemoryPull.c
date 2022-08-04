// "Copyright 2022 <Olimpiev Y.>"
#include "MemoryPull.h"

// Global pull
TMemoryPull globalMemPull = {NULL, 0, 0};


void* AllocMem(size_t size_in_bytes) {
  assert(globalMemPull.Capacity >= size_in_bytes);
  globalMemPull.Capacity -= size_in_bytes;
  void* toRet = &(globalMemPull.Memory[globalMemPull.NotUsedMemIndex]);
  globalMemPull.NotUsedMemIndex += size_in_bytes;
  return toRet;
}

void FreePull(TMemoryPull pull) {
  free(pull.Memory);
}
