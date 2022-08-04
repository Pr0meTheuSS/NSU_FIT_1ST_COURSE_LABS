// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Heap.h"
#include "Queue.h"
#include "BitStreamer.h"

#ifndef ALPHABET_SIZE
  #define ALPHABET_SIZE 256
#endif

typedef struct TCode TCode;
typedef struct TCodeTree TCodeTree;

struct TCode {
  unsigned char Code[40];
  unsigned char CodeLen;
};

struct TCodeTree {
  TCodeTree* LeftChild;
  TCodeTree* RightChild;
  unsigned int Symbol;
  size_t Freq;
};


TCodeTree* InitCodeTreeNode(unsigned int s_code, size_t freq);

TCodeTree* Union(TCodeTree* first, TCodeTree* second);

void FreeTree(TCodeTree* tree);

int IsTerminalNode(TCodeTree* tree_node);

void RecursiveBuildCodeTable(TCodeTree* code_tree, TCode* table, TCode code);

void BuildCodeTable(TCodeTree* code_tree, TCode* table);

TCodeTree* BuildCodeTree(FILE* in);

TCodeTree* ReadCodeTree(TBitStream* stream);

int PutCodeTreeOut(TCodeTree* code_tree, TBitStream* stream);
