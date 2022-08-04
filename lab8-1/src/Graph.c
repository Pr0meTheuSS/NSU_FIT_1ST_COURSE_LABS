// Copyright [2022] <Olimpiev Y.>
#include "Graph.h"


TGraph* InitGraph(size_t nodes_amount, size_t edges_amount) {
    TGraph* graph = (TGraph*)calloc(1, sizeof(TGraph));
    assert(graph);
    graph->NodesAmount = nodes_amount;
    graph->EdgesAmount = edges_amount;
    graph->Edges = (TEdge*)calloc(graph->EdgesAmount, sizeof(TEdge));
    assert(graph->Edges);
    return graph;
}


void AppendEdge(TGraph* graph, NodeIndexType start,
                NodeIndexType finish,
                EdgeWeightType weight) {
    assert(graph);
    assert(graph->CurrEdgeIndex < graph->EdgesAmount);
    TEdge newEdge = { start, finish, weight };
    graph->Edges[graph->CurrEdgeIndex] = newEdge;
    graph->CurrEdgeIndex++;
}


void FreeGraph(TGraph* graph) {
    if (graph) {
        free(graph->Edges);
    }
}


TGraph* ReadGraph(FILE* in) {
    assert(in);
    size_t nodesAmount = 0;
    if (fscanf(in, "%zu", &nodesAmount) != 1) {
        ExitWithError(BadNumberOfLines);
    }
    if (nodesAmount > 5000) {
        ExitWithError(BadNumberOfVertices);
    }
    if (nodesAmount == 0) {
        ExitWithError(NoSpanningTree);
    }
    size_t edgesAmount = 0;
    if (fscanf(in, "%zu", &edgesAmount) != 1) {
        ExitWithError(BadNumberOfLines);
    }
    size_t nodesAmountSupremum = nodesAmount * (nodesAmount - 1) / 2;
    if (edgesAmount > nodesAmountSupremum) {
        ExitWithError(BadNumberOfEdges);
    }
    TGraph* graph = InitGraph(nodesAmount, edgesAmount);
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
