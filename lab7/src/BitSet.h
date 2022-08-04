// "Copyright [2022] Y.Olimpiev"
#pragma once
#include <stdlib.h>
#define BITS_IN_BYTES 8

typedef unsigned char u_char;

typedef struct TBitSet {
    u_char* Set;
    size_t SizeInBytes;
} TBitSet;

u_char GetBit(TBitSet bit_set, size_t index);

void SetBit(TBitSet bit_set, size_t index);
