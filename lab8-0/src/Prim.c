// "Copyright [2022] <Olimpiev Y.>"
#include "Prim.h"


void PrintAnswer(TEdge* edges, TNodeIndexType amount) {
  assert(edges);
  for (TNodeIndexType i = 0; i < amount; i++) {
    printf(const_spec_str_node_index_type, edges[i].Start + 1);
    printf(" ");
    printf(const_spec_str_node_index_type, edges[i].Finish + 1);
    printf("\n");
  }
}


int Prim(TGraph* graph, ui start) {
  TEdgeWeightType currAnswerIndex = 0;
  MarkAsVisited(graph, start);
  TEdge* answer = (TEdge*)calloc(graph->NodesAmount - 1, sizeof(*answer));
  assert(answer);

  TPriorityQueue incedenceEdges = GetAllUnvisitedIncedenceEdges(*graph, start);
  TEdge minEdge;

  while (DeQueue(&incedenceEdges, &minEdge) == EXIT_SUCCESS) {
    if (!WasVisited(*graph, minEdge.Finish)) {
      MarkAsVisited(graph, minEdge.Finish);

      answer[currAnswerIndex] = minEdge;
      currAnswerIndex++;

      TPriorityQueue currQ = GetAllUnvisitedIncedenceEdges(*graph, minEdge.Finish);
      TEdge currEdge;
      while (DeQueue(&currQ, &currEdge) == EXIT_SUCCESS) {
        EnQueue(&incedenceEdges, currEdge, currEdge.Weight);
      }
      FilterQueue(&incedenceEdges, graph->NodesAmount);
    }
  }

  if (currAnswerIndex == graph->NodesAmount - 1) {
    PrintAnswer(answer, currAnswerIndex);
  } else {
    printf("no spanning tree");
  }

  free(answer);
  FreeGraph(graph);
  return EXIT_SUCCESS;
}
