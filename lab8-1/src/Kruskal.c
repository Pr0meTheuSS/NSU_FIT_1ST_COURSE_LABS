// Copyright [2022] <Olimpiev Y.>
#include "Kruskal.h"


int KruskalMinSpanningTree(TGraph graph, FILE* out) {
    assert(out);
    QSort(graph.Edges, graph.EdgesAmount);
    TDSUElement* nodes = (TDSUElement*)calloc(graph.NodesAmount,
                                              sizeof(TDSUElement));
    assert(nodes);
    for (size_t i = 0; i < graph.NodesAmount; i++) {
        nodes[i].Value = i;
    }
    assert(graph.NodesAmount >= 1);
    size_t* answersIndex = (size_t*)calloc(graph.NodesAmount, sizeof(size_t));
    assert(answersIndex);
    unsigned int currAnswersIndex = 0;
    for (size_t i = 0; i < graph.EdgesAmount; i++) {
        TEdge currEdge = graph.Edges[i];
        if (Union(&nodes[currEdge.Start], &nodes[currEdge.Finish]) == EXIT_SUCCESS) {
            answersIndex[currAnswersIndex] = i;
            currAnswersIndex++;
        }
    }

    int retCode = NoSpanningTree;
    if (currAnswersIndex == graph.NodesAmount - 1) {
        for (size_t i = 0; i < currAnswersIndex; i++) {
            fprintf(out, "%u %u\n", graph.Edges[answersIndex[i]].Start + 1,
                                    graph.Edges[answersIndex[i]].Finish + 1);
        }
        retCode = EXIT_SUCCESS;
    }
    free(answersIndex);
    free(nodes);
    return retCode;
}
