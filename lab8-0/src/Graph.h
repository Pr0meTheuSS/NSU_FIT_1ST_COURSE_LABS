// "Copyright [2022] <Olimpiev Y.>"
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>  // for INT_MAX
#include "Service.h"
#include "Exception.h"


struct TEdge {
  ui Start;
  ui Finish;
  ui Weight;
};


struct TGraph {
  TEdgeWeightType* AdjMatrix;
  bool* IsVisited;
  TNodeIndexType NodesAmount;
};


TGraph* InitGraph(TNodeIndexType nodes_amount);

void FreeGraph(TGraph* graph);

TGraph* ReadGraph(FILE* in);

void MarkAsVisited(TGraph* graph, TNodeIndexType node_index);

void AppendEdge(TGraph* graph, TNodeIndexType start, TNodeIndexType finish, TEdgeWeightType weight);

TEdgeWeightType GetWeight(TGraph graph, TNodeIndexType start, TNodeIndexType finish);

bool PathExist(TGraph graph, TNodeIndexType start, TNodeIndexType finish);

bool WasVisited(TGraph graph, TNodeIndexType node_index);
