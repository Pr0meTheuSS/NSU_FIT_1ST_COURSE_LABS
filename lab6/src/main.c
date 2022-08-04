// "Copyright 2022 <Olimpiev Y.>"
#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"


extern TMemoryPull globalMemPull;


int CustomScanAVLTreeValue(int* value) {
  // If scanf success - return true
  return (scanf("%d", value) == 1);
}


void CustomPrintAVLTreeHeight(TAVLTree tree) {
  printf("%u", GetTreeHeight(tree));
}


int main(void) {
  TAVLTree tree = {NULL};
  size_t valCount = 0;

  if (scanf("%zu", &valCount) != 1) {
    perror("\nWrong input\n");
    exit(-1);
  }
  // Initial global memory pull
  globalMemPull.Memory = calloc(valCount, sizeof(TAVLTreeNode));
  globalMemPull.Capacity = valCount * sizeof(TAVLTreeNode);
  globalMemPull.NotUsedMemIndex = 0;

  assert(globalMemPull.Memory);
  for (size_t i = 0; i < valCount; i++) {
    AVLNodeValueType val;
    if (!CustomScanAVLTreeValue(&val)) {
      perror("\nWrong input\n");
      exit(-1);
    }
    AddValue(&tree, val);
  }
  CustomPrintAVLTreeHeight(tree);
  FreePull(globalMemPull);
  return EXIT_SUCCESS;
}
