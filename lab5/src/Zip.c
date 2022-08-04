// "Copyright 2022 <Olimpiev Y.>"
#include "Zip.h"

void PrintUnWrittenBits(TBitStream* s) {
    assert(s);
    if (s->BufferPosition) {
        fwrite(s->Buffer, sizeof(s->Buffer[0]), s->BufferPosition, s->Stream);
        s->BufferPosition = 0;
    }
    if (s->SignificantPartLen) {
        fprintf(s->Stream, "%c", s->Byte);
        s->SignificantPartLen = 0;
        s->Byte = 0;
    }
}

int Compress(FILE* in, FILE* out) {
    assert(in);
    assert(out);
    TCode codeTable[ALPHABET_SIZE] = { { { 0 }, 0 } };
    TCodeTree* codeTree = BuildCodeTree(in);
    if (!codeTree) {
      // EXIT_SUCCESS for tests
      return EXIT_SUCCESS;
    }
    BuildCodeTable(codeTree, codeTable);
    TBitStream* stream = InitBitStream(out);

    int status = PutCodeTreeOut(codeTree, stream);
    if (status != EXIT_SUCCESS) {
      goto finally;
    }
    status = PutCompressedData(in, stream, codeTable);
    if (status != EXIT_SUCCESS) {
      goto finally;
    }
    finally:
      FreeTree(codeTree);
      DestroyBitStream(stream);
      return status;
}

int Decompress(FILE* in, FILE* out) {
    assert(in);
    assert(out);

    TBitStream* stream = InitBitStream(in);

    TCodeTree* codeTree = ReadCodeTree(stream);
    int ret = PutDecompressedData(stream, out, codeTree);
    FreeTree(codeTree);
    DestroyBitStream(stream);
    return ret;
}

int Zip(FILE* in, FILE* out, char mode) {
    assert(in);
    assert(out);
    if (mode == 'c') {
        return Compress(in, out);
    } else if (mode == 'd') {
      return Decompress(in, out);
    } else {
      return EXIT_FAILURE;
    }
}

// Stream-но work-ает //
int PutDecompressedData(TBitStream* stream, FILE* out, TCodeTree* code_tree) {
  assert(stream);
  assert(out);

  int prevPos = ftell(stream->Stream);
  fseek(stream->Stream, -1, SEEK_END);
  int fileEnd = ftell(stream->Stream);
  unsigned char unsignPartLen = 0;
  if (fscanf(stream->Stream, "%c", &unsignPartLen) != 1) {
    perror("Wrong Input!");
    exit(0);
  }
  fseek(stream->Stream, prevPos, SEEK_SET);

  TBitStream* outStream = InitBitStream(out);

  int currByteIndex = prevPos;
  TCodeTree* currNode = code_tree;

  while (currByteIndex != fileEnd ||
         stream->SignificantPartLen >= unsignPartLen) {
    if (!currNode->LeftChild && !currNode->RightChild) {
      for (size_t i = 0; i < BITS_IN_BYTE; i++) {
        PrintBit(outStream, GetBit(currNode->Symbol, i));
      }
      currNode = code_tree;
      continue;
    }
    if (currByteIndex == fileEnd &&
        stream->SignificantPartLen <= unsignPartLen) {
      break;
    }
    unsigned char curBit = ReadBit(stream);
    if (stream->SignificantPartLen >= 7) {
      currByteIndex++;
    }
    if (curBit) {
      currNode = currNode->RightChild;
    } else {
      currNode = currNode->LeftChild;
    }
  }
  PrintUnWrittenBits(outStream);
  DestroyBitStream(outStream);
  return EXIT_SUCCESS;
}

int PutCompressedData(FILE* in,
                      TBitStream* stream,
                      TCode code_table[ALPHABET_SIZE]) {
  assert(in);
  assert(stream);
  // Go to begin of Text except zipMode-symbol
  fseek(in, 1, SEEK_SET);

  int s = 0;
  while ((s = fgetc(in)) != -1) {
    TCode currCode = code_table[s];
    for (int i = 0; i < currCode.CodeLen; i++) {
      PrintBit(stream, currCode.Code[i] == '1' ? 1 : 0);
    }
  }
  unsigned char unsignicantPartLen = (BITS_IN_BYTE - stream->SignificantPartLen) % 8;
  while (stream->SignificantPartLen != 0) {
    PrintBit(stream, 0);
  }
  PrintUnWrittenBits(stream);
  fprintf(stream->Stream, "%c", unsignicantPartLen);
  return EXIT_SUCCESS;
}
