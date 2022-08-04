// "Copyright 2022 <Olimpiev Y.>"
#include "AVLTree.h"
extern TMemoryPull globalMemPull;

AVLNodeValueType max(AVLNodeValueType val1, AVLNodeValueType val2) {
  return (val1 > val2)? val1: val2;
}


AVLNodeValueType min(AVLNodeValueType val1, AVLNodeValueType val2) {
  return (val1 < val2)? val1: val2;
}


AVLNodeValueType Abs(AVLNodeValueType val1, AVLNodeValueType val2) {
  return max(val1, val2) - min(val1, val2);
}


/* Interface */

eAVLTreeStatus AddValue(TAVLTree* tree, AVLNodeValueType value) {
  if (!tree) {
    return WrongArgs;
  }
  tree->Root = AddNodeToTree(tree->Root, value);
  assert(tree->Root);
  return Success;
}


AVLTreeHeightType GetTreeHeight(TAVLTree tree) {
  return GetNodeHeight(tree.Root);
}

/* Rebalance*/

int IsNeedRebalance(TAVLTreeNode node) {
  return Abs(GetNodeHeight(node.LeftChild), GetNodeHeight(node.RightChild)) > 1;
}


TAVLTreeNode* RebalanceNode(TAVLTreeNode* node) {
  assert(node);
  if (GetNodeHeight(node->RightChild) > GetNodeHeight(node->LeftChild)) {
    if (GetNodeHeight(node->RightChild->LeftChild) > GetNodeHeight(node->RightChild->RightChild)) {
      return RotateBigLeft(node);
    } else {
      return RotateSmallLeft(node);
    }
  }
  if (GetNodeHeight(node->RightChild) < GetNodeHeight(node->LeftChild)) {
    if (GetNodeHeight(node->LeftChild->LeftChild) < GetNodeHeight(node->LeftChild->RightChild)) {
      return RotateBigRight(node);
    } else {
      return RotateSmallRight(node);
    }
  }
  return node;
}


TAVLTreeNode* RotateSmallLeft(TAVLTreeNode* tree) {
  assert(tree);
  TAVLTreeNode* newRoot =  tree->RightChild;
  tree->RightChild = newRoot->LeftChild;
  newRoot->LeftChild = tree;
  return newRoot;
}


TAVLTreeNode* RotateSmallRight(TAVLTreeNode* tree) {
  assert(tree);
  TAVLTreeNode* newRoot =  tree->LeftChild;
  tree->LeftChild = newRoot->RightChild;
  newRoot->RightChild = tree;
  return newRoot;
}

TAVLTreeNode* RotateBigLeft(TAVLTreeNode* tree) {
  assert(tree);
  tree->RightChild = RotateSmallRight(tree->RightChild);
  tree = RotateSmallLeft(tree);
  return tree;
}

TAVLTreeNode* RotateBigRight(TAVLTreeNode* tree) {
  assert(tree);
  tree->LeftChild = RotateSmallLeft(tree->LeftChild);
  tree = RotateSmallRight(tree);
  return tree;
}


/* TAVLTreeNode methods */

TAVLTreeNode* AddNodeToTree(TAVLTreeNode* currNode, AVLNodeValueType value) {
  if (!currNode) {
    return InitNode(value);
  }
  if (currNode->Value <= value) {
    currNode->RightChild = AddNodeToTree(currNode->RightChild, value);
  } else {
    currNode->LeftChild = AddNodeToTree(currNode->LeftChild, value);
  }
  if (IsNeedRebalance(*currNode)) {
    currNode = RebalanceNode(currNode);
  }
  UpdateNodeHeight(currNode->RightChild);
  UpdateNodeHeight(currNode->LeftChild);
  UpdateNodeHeight(currNode);

  return currNode;
}


AVLTreeHeightType GetNodeHeight(TAVLTreeNode* node) {
  if (!node) {
    return 0;
  }
  return node->Height;
}


eAVLTreeStatus UpdateNodeHeight(TAVLTreeNode* node) {
  if (!node) {
    return WrongArgs;
  }
  node->Height = max(GetNodeHeight(node->RightChild), GetNodeHeight(node->LeftChild)) + 1;
  return Success;
}


TAVLTreeNode* InitNode(AVLNodeValueType value) {
  TAVLTreeNode* newNode = AllocMem(sizeof(TAVLTreeNode));
  assert(newNode);
  newNode->LeftChild = newNode->RightChild = NULL;
  memcpy(&newNode->Value, &value, sizeof(value));
  newNode->Height = 1;
  return newNode;
}
