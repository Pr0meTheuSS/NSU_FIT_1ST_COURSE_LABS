// "Copyright [2022] Y.Olimpiev"
#pragma once
#include <stdlib.h>
#include <assert.h>
#include "BitSet.h"
#include "Exception.h"

typedef unsigned int u_int;
/* +++++++++++++++++++++++ ARRAY +++++++++++++++++++++++*/

typedef struct TArray {
    unsigned int* Array;
    size_t IndexToAppend;
} TArray;

void AddToArray(TArray* answer, unsigned int node_index);

/* +++++++++++++++++++++++ GRAPH +++++++++++++++++++++++*/
typedef enum EColor {
    White,
    Gray,
    Black
} EColor;


typedef struct TGraph {
    TBitSet AdjMatrix;
    TArray Answer;
    EColor* Colors;
    size_t NodesAmount;
} TGraph;
void PrintGraph(TGraph* g);


TGraph* InitGraph(size_t nodes_amount);

void AddEdge(TGraph* graph, u_int from, u_int to);

u_char GetPath(TGraph* graph, u_int from, u_int to);

void FreeGraph(TGraph* g);

TGraph* ReadGraph();

void PaintBlack(TGraph* g, u_int node_index);

void PaintGray(TGraph* g, u_int node_index);

int IsGray(TGraph* g, u_int node_index);

int IsBlack(TGraph* g, u_int node_index);

int IsFullBypass(TGraph* g);

int TopDFS(TGraph* g, u_int start);

void PrintAnswer(TGraph* g);

int TopSort(TGraph* g);
