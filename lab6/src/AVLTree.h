// "Copyright 2022 <Olimpiev Y.>"
#pragma once
#include <assert.h>  // for assert()
#include <stdlib.h>  // for abs()
#include <string.h>  // for memcpy()
#include <stdio.h>  // for debug
#include "MemoryPull.h"  // For custom memory manage


typedef int AVLNodeValueType;
typedef unsigned int AVLTreeHeightType;

typedef enum eAVLTreeStatus {
  WrongArgs,
  Success
}eAVLTreeStatus;

typedef struct TAVLTreeNode {
  struct TAVLTreeNode* RightChild;
  struct TAVLTreeNode* LeftChild;
  AVLTreeHeightType Height;
  AVLNodeValueType Value;
} TAVLTreeNode;


typedef struct TAVLTree {
  TAVLTreeNode* Root;
} TAVLTree;


// Tree user interface
eAVLTreeStatus AddValue(TAVLTree* tree, AVLNodeValueType value);
AVLTreeHeightType GetTreeHeight(TAVLTree tree);

// Functions for rebalance tree
int IsNeedRebalance(TAVLTreeNode node);
TAVLTreeNode* RebalanceNode(TAVLTreeNode* node);
TAVLTreeNode* RotateSmallLeft(TAVLTreeNode* tree);
TAVLTreeNode* RotateSmallRight(TAVLTreeNode* tree);
TAVLTreeNode* RotateBigLeft(TAVLTreeNode* tree);
TAVLTreeNode* RotateBigRight(TAVLTreeNode* tree);


// TAVLTreeNode's methods
TAVLTreeNode* InitNode(AVLNodeValueType Value);
TAVLTreeNode* AddNodeToTree(TAVLTreeNode* currNode, AVLNodeValueType value);
AVLTreeHeightType GetNodeHeight(TAVLTreeNode* tree);
eAVLTreeStatus UpdateNodeHeight(TAVLTreeNode* node);
