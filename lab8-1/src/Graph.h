// Copyright [2022] <Olimpiev Y.>
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "Exception.h"


typedef unsigned int NodeIndexType;
typedef unsigned int EdgeWeightType;

struct TEdge {
    NodeIndexType Start;
    NodeIndexType Finish;
    EdgeWeightType Weight;
};


struct TGraph {
    struct TEdge* Edges;
    size_t EdgesAmount;
    size_t NodesAmount;
    size_t CurrEdgeIndex;
};

typedef struct TGraph TGraph;
typedef struct TEdge TEdge;


TGraph* InitGraph(size_t nodes_amount, size_t edges_amount);

void FreeGraph(TGraph* graph);

void AppendEdge(TGraph* graph, NodeIndexType start, 
                NodeIndexType finish, EdgeWeightType weight);

TGraph* ReadGraph(FILE* in);
