// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifndef BITS_IN_BYTE
  #define BITS_IN_BYTE 8
#endif

#ifndef STREAM_BUFFER_SIZE
  #define STREAM_BUFFER_SIZE 256000
#endif

// BIT Streamer //
typedef struct TBitStream TBitStream;

struct TBitStream {
  FILE* Stream;
  unsigned char Byte;
  unsigned char Buffer[STREAM_BUFFER_SIZE];
  unsigned int BufferPosition;
  unsigned char SignificantPartLen;
};

TBitStream* InitBitStream(FILE* stream);

void DestroyBitStream(TBitStream* bs);

unsigned char GetBit(unsigned char byte, size_t index);

void PrintBit(TBitStream* bs, unsigned char bit);

unsigned char ReadBit(TBitStream* bs);
