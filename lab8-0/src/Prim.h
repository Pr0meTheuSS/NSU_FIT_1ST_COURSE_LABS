// "Copyright [2022] <Olimpiev Y.>"
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "PriorityQueue.h"
#include "Service.h"


void PrintAnswer(TEdge* edges, TNodeIndexType amount);

int Prim(TGraph* graph, TNodeIndexType start);
