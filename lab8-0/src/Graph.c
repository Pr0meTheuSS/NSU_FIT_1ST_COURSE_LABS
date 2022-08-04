  //  "Copyright [2022] <Olimpiev Y.>"
#include "Graph.h"


void MarkAsVisited(TGraph* graph, TNodeIndexType node_index) {
  assert(node_index < graph->NodesAmount);
  graph->IsVisited[node_index] = true;
}


TGraph* InitGraph(TNodeIndexType nodes_amount) {
  TGraph* graph = (TGraph*)calloc(1, sizeof(*graph));
  assert(graph);
  graph->NodesAmount = nodes_amount;

  graph->IsVisited = (bool*)calloc(graph->NodesAmount, sizeof(bool));
  assert(graph->IsVisited);
  TNodeIndexType cellsAmount = graph->NodesAmount * (graph->NodesAmount + 1) / 2;
  graph->AdjMatrix = (TEdgeWeightType*)calloc(cellsAmount,
                                              sizeof(TEdgeWeightType));
  assert(graph->AdjMatrix);
  return graph;
}


void FreeGraph(TGraph* graph) {
  if (graph) {
    free(graph->AdjMatrix);
    free(graph->IsVisited);
    free(graph);
  }
}


void AppendEdge(TGraph* graph,
                TNodeIndexType start,
                TNodeIndexType finish,
                TEdgeWeightType weight) {
  assert(graph);
  TNodeIndexType maxIndex = max(start, finish);
  TNodeIndexType minIndex = min(start, finish);
  // Индексы для канторовской нумерации
  graph->AdjMatrix[GetCellNumber(minIndex, graph->NodesAmount - 1 - maxIndex)] = weight;
}


TGraph* ReadGraph(FILE* in) {
  assert(in);
  TNodeIndexType nodesAmount = 0;
  if (fscanf(in, "%u", &nodesAmount) != 1) {
    ExitWithError(BadNumberOfLines);
  }
  if (nodesAmount > 5000) {
    ExitWithError(BadNumberOfVertices);
  }
  if (nodesAmount == 0) {
    ExitWithError(NoSpanningTree);
  }
  TGraph* graph = InitGraph(nodesAmount);
  assert(graph);
  ui edgesAmount = 0;
  if (fscanf(in, "%u", &edgesAmount) != 1) {
    FreeGraph(graph);
    ExitWithError(BadNumberOfLines);
  }
  TNodeIndexType nodesAmountSupremum = graph->NodesAmount * (graph->NodesAmount - 1) / 2;
  if (edgesAmount > nodesAmountSupremum) {
    FreeGraph(graph);
    ExitWithError(BadNumberOfEdges);
  }
  for (size_t i = 0; i < edgesAmount; i++) {
    size_t from_index = 0;
    size_t to_index = 0;
    size_t weight = 0;

    if (fscanf(in, "%zu %zu %zu", &from_index, &to_index, &weight) != 3) {
      FreeGraph(graph);
      ExitWithError(BadNumberOfLines);
    }
    if (from_index > graph->NodesAmount ||
      to_index > graph->NodesAmount) {
      FreeGraph(graph);
      ExitWithError(BadVertex);
    }
    if (weight > INT_MAX) {
      FreeGraph(graph);
      ExitWithError(BadLength);
    }
    AppendEdge(graph, from_index - 1, to_index - 1, weight);
  }
  return graph;
}


TEdgeWeightType GetWeight(TGraph graph,
                          TNodeIndexType start,
                          TNodeIndexType finish) {
  TNodeIndexType maxIndex = max(start, finish);
  TNodeIndexType minIndex = min(start, finish);
  return graph.AdjMatrix[GetCellNumber(minIndex, graph.NodesAmount - 1 - maxIndex)];
}


bool PathExist(TGraph graph,
               TNodeIndexType start,
               TNodeIndexType finish) {
  return (GetWeight(graph, start, finish) != 0);
}


bool WasVisited(TGraph graph, TNodeIndexType node_index) {
  assert(node_index < graph.NodesAmount);
  return graph.IsVisited[node_index];
}
