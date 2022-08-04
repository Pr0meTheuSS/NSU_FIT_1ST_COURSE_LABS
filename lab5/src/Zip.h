// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include "CodeTree.h"
#include "BitStreamer.h"

#ifndef ALPHABET_SIZE
  #define ALPHABET_SIZE 256
#endif

#ifndef ALPHABET_SIZE
  #define BITS_IN_BYTE 8
#endif

#include "Zip.h"
// ZIP part //
// Stream-но work-ает //

int Compress(FILE* in, FILE* out);

int Decompress(FILE* in, FILE* out);

int Zip(FILE* in, FILE* out, char mode);

int PutDecompressedData(TBitStream* stream, FILE* out, TCodeTree* code_tree);

int PutCompressedData(FILE* in,
                      TBitStream* stream,
                      TCode code_table[ALPHABET_SIZE]);
