// "Copyright 2022 <Olimpiev Y.>"
#include "CodeTree.h"

TCodeTree* InitCodeTreeNode(unsigned int s_code, size_t freq) {
  TCodeTree* newNode = (TCodeTree*)calloc(1, sizeof(TCodeTree));
  assert(newNode);
  newNode->Symbol = s_code;
  newNode->Freq = freq;
  return newNode;
}

int IsTerminalNode(TCodeTree* node) {
  assert(node);
  return (!node->RightChild && !node->LeftChild);
}

TCodeTree* Union(TCodeTree* first, TCodeTree* second) {
  assert(first);
  assert(second);
  TCodeTree* root = InitCodeTreeNode(0, first->Freq + second->Freq);
  root->LeftChild = first;
  root->RightChild = second;
  return root;
}

void FreeTree(TCodeTree* tree) {
  if (tree) {
    FreeTree(tree->LeftChild);
    FreeTree(tree->RightChild);
    free(tree);
  }
}

void RecursiveBuildCodeTable(TCodeTree* code_tree, TCode* table, TCode code) {
  assert(table);
  assert(code_tree);
  if (IsTerminalNode(code_tree)) {
    table[code_tree->Symbol] = code;
    return;
  }
  if (code_tree->LeftChild) {
    code.CodeLen++;
    RecursiveBuildCodeTable(code_tree->LeftChild, table, code);
    code.CodeLen--;
  }
  if (code_tree->LeftChild) {
    code.Code[code.CodeLen] = '1';
    code.CodeLen++;
    RecursiveBuildCodeTable(code_tree->RightChild, table, code);
    code.CodeLen--;
  }
}

void BuildCodeTable(TCodeTree* code_tree, TCode* table) {
    assert(table);
    TCode code = { { 0 }, 0 };
    RecursiveBuildCodeTable(code_tree, table, code);
}


TCodeTree* BuildCodeTree(FILE* in) {
  assert(in);
  // Go to begin of the Text
  fseek(in, 1, SEEK_SET);
  int s = 0;
  size_t freqTable[ALPHABET_SIZE] = { 0 };

  while ((s = fgetc(in)) != EOF) {
    freqTable[s]++;
  }

  THeap* heap = InitHeap(ALPHABET_SIZE * 2 + 1);;
  for (size_t s = 0; s < ALPHABET_SIZE; s++) {
    if (freqTable[s]) {
      TCodeTree* newNode = InitCodeTreeNode(s, freqTable[s]);
      AddToHeap(heap, &newNode, newNode->Freq);
    }
  }
  TCodeTree* node1 = NULL;
  TCodeTree* node2 = NULL;
  while (GetRoot(heap, &node1) == EXIT_SUCCESS &&
    GetRoot(heap, &node2) == EXIT_SUCCESS) {
    node1 = Union(node1, node2);
    AddToHeap(heap, &node1, node1->Freq);
  }
  FreeHeap(heap);
  if (!node2 && node1) {
    // Fictive node for saving tree code invariant
    node2 = InitCodeTreeNode(0, 0);
    node1 = Union(node1, node2);
  }
  return node1;
}

void ReadByteBitByBit(unsigned char* byte, TBitStream* stream) {
  assert(byte);
  assert(stream);
  for (size_t i = 0; i < BITS_IN_BYTE; i++) {
    if (ReadBit(stream)) {
      *byte |= 1 << (BITS_IN_BYTE - i - 1);
    }
  }
}

void PrintByteBitByBit(TBitStream* stream, unsigned char byte) {
  assert(stream);
  for (size_t i = 0; i < BITS_IN_BYTE; i++) {
    PrintBit(stream, GetBit(byte, i));
  }
}

TCodeTree* ReadCodeTree(TBitStream* stream) {
  assert(stream);
  TCodeTree* root = (TCodeTree*)calloc(1, sizeof(TCodeTree));
  assert(root);
  TQueue queue = { NULL, NULL };
  TCodeTree* currNode = root;
  do {
    unsigned char currBit = ReadBit(stream);
    if (currBit) {
      currNode->LeftChild = InitCodeTreeNode(0, 0);
      EnQueue(&queue, &currNode->LeftChild);
    } else {
      unsigned char code = 0;
      ReadByteBitByBit(&code, stream);
      currNode->LeftChild = InitCodeTreeNode(0, 0);
      currNode->LeftChild->Symbol = code;
    }
    currBit = ReadBit(stream);
    if (currBit) {
        currNode->RightChild = InitCodeTreeNode(0, 0);
        EnQueue(&queue, &currNode->RightChild);
    } else {
      unsigned char code = 0;
      ReadByteBitByBit(&code, stream);
      currNode->RightChild = InitCodeTreeNode(0, 0);
      currNode->RightChild->Symbol = code;
    }
  } while (DeQueue(&queue, &currNode) == EXIT_SUCCESS);
  return root;
}

int PutCodeTreeOut(TCodeTree* code_tree, TBitStream* stream) {
  assert(stream);
  TQueue queue = { NULL, NULL };

  EnQueue(&queue, &code_tree);
  TCodeTree* currNodePtr;
  while (DeQueue(&queue, &currNodePtr) == EXIT_SUCCESS) {
    if (currNodePtr->LeftChild) {
      if (IsTerminalNode(currNodePtr->LeftChild)) {
        PrintBit(stream, 0);
        PrintByteBitByBit(stream, currNodePtr->LeftChild->Symbol);
      } else {
        PrintBit(stream, 1);
        EnQueue(&queue, &currNodePtr->LeftChild);
      }
    }
    if (currNodePtr->RightChild) {
      if (IsTerminalNode(currNodePtr->RightChild)) {
        PrintBit(stream, 0);
        PrintByteBitByBit(stream, currNodePtr->RightChild->Symbol);
      } else {
        PrintBit(stream, 1);
        EnQueue(&queue, &currNodePtr->RightChild);
      }
    }
  }
  return EXIT_SUCCESS;
}
