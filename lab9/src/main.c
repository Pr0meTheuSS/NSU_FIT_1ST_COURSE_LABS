// "Copyright [2022] <Olimpiev Y.>"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#define pass
#define true 1
#define false 0
#define MAX_NODES_AMOUNT 5000
#define INF UINT_MAX

typedef char bool;
typedef unsigned int ui;

typedef struct TGraph {
  ui DistanceMarks[MAX_NODES_AMOUNT];
  ui Parents[MAX_NODES_AMOUNT];
  ui** AdjMatrix;
  bool* IsVisited;
  ui NodesAmount;
  ui FinishVisitsAmount;
} TGraph;

static inline int GetMinWeightIndex(TGraph* graph) {
  int minWeightIndex = -1;
  size_t minWeight = INF;
  for (size_t i = 0; i < graph->NodesAmount; i++) {
    if (!graph->IsVisited[i] && graph->DistanceMarks[i] < minWeight) {
      minWeight = graph->DistanceMarks[i];
      minWeightIndex = i;
    }
  }
  return minWeightIndex;
}

typedef enum EExitCode {
  NoSpanningTree,
  BadNumberOfVertices,
  BadNumberOfLines,
  BadNumberOfEdges,
  BadVertex,
  BadLength
} EExitCode;

const char* ErrorMsg(EExitCode e) {
  switch (e) {
  case BadNumberOfVertices:
    return "bad number of vertices";
  case BadNumberOfLines:
    return "bad number of lines";
  case BadNumberOfEdges:
    return "bad number of edges";
  case BadVertex:
    return "bad vertex";
  case BadLength:
    return "bad length";
  case NoSpanningTree:
  return "no spanning tree";
  default:
    return NULL;
  }
}

void ExitWithError(EExitCode e) {
  printf("%s", ErrorMsg(e));
  exit(0);
}

TGraph* InitGraph(ui nodes_amount) {
  TGraph* graph = (TGraph*)calloc(1, sizeof(TGraph));
  assert(graph);
  graph->NodesAmount = nodes_amount;

  graph->IsVisited = (bool*)calloc(graph->NodesAmount, sizeof(bool));
  assert(graph->IsVisited);

  graph->AdjMatrix = (ui**)calloc(graph->NodesAmount, sizeof(ui*));
  assert(graph->AdjMatrix);
  for (size_t i = 0; i < nodes_amount; i++) {
    graph->AdjMatrix[i] = (ui*)calloc(graph->NodesAmount, sizeof(ui));
    assert(graph->AdjMatrix[i]);
    graph->DistanceMarks[i] = INF;
    graph->Parents[i] = i;
  }
  return graph;
}

void FreeGraph(TGraph* graph) {
  if (graph) {
    for (size_t i = 0; i < graph->NodesAmount; i++) {
      free(graph->AdjMatrix[i]);
    }
    free(graph->AdjMatrix);
    free(graph->IsVisited);
  }
  free(graph);
}

static inline void AppendEdge(TGraph* graph, ui start, ui finish, ui weight) {
  assert(graph);
  graph->AdjMatrix[start][finish] = graph->AdjMatrix[finish][start] = weight;
}

TGraph* ReadGraph(FILE* in,
                  size_t* start_vertex_index,
                  size_t* finish_vertex_index) {
  assert(in);
  size_t nodesAmount = 0;
  if (fscanf(in, "%zu", &nodesAmount) != 1) {
    ExitWithError(BadNumberOfLines);
  }
  if (nodesAmount > MAX_NODES_AMOUNT) {
    ExitWithError(BadNumberOfVertices);
  }
  if (fscanf(in, "%zu %zu", start_vertex_index, finish_vertex_index) != 2) {
    ExitWithError(BadNumberOfLines);
  }
  if (*start_vertex_index > nodesAmount ||
    *start_vertex_index == 0 ||
    *finish_vertex_index > nodesAmount ||
    *finish_vertex_index == 0) {
    ExitWithError(BadVertex);
  }
  size_t edgesAmount = 0;
  if (fscanf(in, "%zu", &edgesAmount) != 1) {
    ExitWithError(BadNumberOfLines);
  }
  size_t nodesAmountSupremum = nodesAmount * (nodesAmount - 1) / 2;
  if (edgesAmount > nodesAmountSupremum) {
    ExitWithError(BadNumberOfEdges);
  }
  TGraph* graph = InitGraph(nodesAmount);
  assert(graph);
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

int Deykstra(TGraph* graph, size_t start_node_index, size_t finish_node_index) {
  graph->DistanceMarks[start_node_index] = 0;
  int currIndex = start_node_index;

  do {
    graph->IsVisited[currIndex] = true;

    for (size_t i = 0; i < graph->NodesAmount; i++) {
      if (graph->AdjMatrix[currIndex][i]) {
        if (i == finish_node_index) {
          graph->FinishVisitsAmount++;
        }
        if (!graph->IsVisited[i]) {
          if (graph->DistanceMarks[i] > graph->AdjMatrix[currIndex][i] &&
            graph->DistanceMarks[currIndex] < graph->DistanceMarks[i] - graph->AdjMatrix[currIndex][i]) {
            graph->DistanceMarks[i] = graph->AdjMatrix[currIndex][i] + graph->DistanceMarks[currIndex];
            graph->Parents[i] = currIndex;
          }
        }
      }
    }
  } while ((currIndex = GetMinWeightIndex(graph)) != -1);
  return EXIT_SUCCESS;
}

void PrintAllPathsWeights(TGraph* graph) {
  assert(graph);
  for (size_t i = 0; i < graph->NodesAmount; i++) {
    if (graph->IsVisited[i]) {
      if (graph->DistanceMarks[i] <= INT_MAX) {
        printf("%u ", graph->DistanceMarks[i]);
      } else {
        printf("INT_MAX+ ");
      }
    } else {
      printf("oo ");
    }
  }
}

void PrintPath(TGraph* graph, size_t start, size_t finish) {
  assert(graph);
  ui answer[MAX_NODES_AMOUNT] = { 0 };
  size_t currIndex = 0;
  if (!graph->IsVisited[finish]) {
    printf("no path");
  }
  while (finish != start) {
    answer[currIndex] = finish;
    currIndex++;
    finish = graph->Parents[finish];
  }
  for (size_t i = 0; i < currIndex; i++) {
    printf("%d ", answer[i] + 1);
  }
  printf("%zu ", start + 1);
}

void PrintPathFromFinishToStart(TGraph* graph, size_t start, size_t finish) {
  assert(graph);
  if (graph->IsVisited[finish - 1] == false) {
    printf("no path ");
    return;
  }
  if (graph->DistanceMarks[finish - 1] > INT_MAX &&
    graph->FinishVisitsAmount > 1) {
    printf("overflow ");
  } else {
    PrintPath(graph, start - 1, finish - 1);
  }
}

int main(void) {
  size_t startIndexNode = 0;
  size_t finishIndexNode = 0;

  TGraph* graph = ReadGraph(stdin, &startIndexNode, &finishIndexNode);
  int retCode = Deykstra(graph, startIndexNode - 1, finishIndexNode - 1);
  if (retCode != EXIT_SUCCESS) {
    FreeGraph(graph);
    return retCode;
  }
  PrintAllPathsWeights(graph);
  printf("\n");
  PrintPathFromFinishToStart(graph, startIndexNode, finishIndexNode);
  FreeGraph(graph);
  return retCode;
}
