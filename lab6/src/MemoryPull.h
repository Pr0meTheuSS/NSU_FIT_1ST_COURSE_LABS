// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include <stdlib.h>
#include <assert.h>


typedef struct TMemoryPull {
  unsigned char* Memory;
  size_t Capacity;
  size_t NotUsedMemIndex;
} TMemoryPull;

void* AllocMem(size_t size_in_bytes);

void FreePull(TMemoryPull pull);
