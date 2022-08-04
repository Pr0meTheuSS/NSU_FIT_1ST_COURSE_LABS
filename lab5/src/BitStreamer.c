// "Copyright 2022 <Olimpiev Y.>"
#include "BitStreamer.h"

TBitStream* InitBitStream(FILE* stream) {
  TBitStream* ret = (TBitStream*)calloc(1, sizeof(TBitStream));
  assert(ret);
  ret->Stream = stream;
  assert(ret->Stream);
  return ret;
}

void DestroyBitStream(TBitStream* bs) {
  free(bs);
}

unsigned char GetBit(unsigned char byte, size_t index) {
  unsigned char bit = byte & (1 << (BITS_IN_BYTE - index - 1));
  return bit ? 1 : 0;
}

void PrintBit(TBitStream* bs, unsigned char bit) {
  assert(bs);
  bs->Byte |= bit << (BITS_IN_BYTE - bs->SignificantPartLen - 1);
  bs->SignificantPartLen++;

  if (bs->SignificantPartLen > 7) {
    bs->Buffer[bs->BufferPosition] = bs->Byte;
    bs->BufferPosition++;
    if (bs->BufferPosition >= STREAM_BUFFER_SIZE) {
      fwrite(bs->Buffer, sizeof(bs->Buffer[0]), bs->BufferPosition, bs->Stream);
      bs->BufferPosition = 0;
    }
    bs->Byte = 0;
    bs->SignificantPartLen = 0;
  }
}

unsigned char ReadBit(TBitStream* bs) {
  assert(bs);

  if (!bs->SignificantPartLen) {
    if (fscanf(bs->Stream, "%c", &bs->Byte) != 1) {
      perror("Wrong input!");
      exit(0);
    }
    bs->SignificantPartLen = BITS_IN_BYTE;
  }
  bs->SignificantPartLen--;
  unsigned char ret = bs->Byte & (1 << bs->SignificantPartLen);
  return ret ? 1 : 0;
}
