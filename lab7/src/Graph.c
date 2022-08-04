// "Copyright [2022] Y.Olimpiev"
#include "Graph.h"

/* +++++++++++++++++++++++ ARRAY +++++++++++++++++++++++*/

void AddToArray(TArray* answer, unsigned int node_index) {
    assert(answer);
    answer->Array[answer->IndexToAppend] = node_index;
    answer->IndexToAppend++;
}

void PrintAnswer(TGraph* g) {
    for (size_t i = 0; i < g->Answer.IndexToAppend; i++) {
        printf("%u ", g->Answer.Array[g->Answer.IndexToAppend - 1 - i] + 1);
    }
}

/* +++++++++++++++++++++++ GRAPH +++++++++++++++++++++++*/

TGraph* InitGraph(size_t nodes_amount) {
    TGraph* toRet = (TGraph*)calloc(1, sizeof(TGraph));
    assert(toRet);

    toRet->NodesAmount = nodes_amount;
    size_t nodesAmountSqr = toRet->NodesAmount * toRet->NodesAmount;
    toRet->AdjMatrix.SizeInBytes = nodesAmountSqr / BITS_IN_BYTES;
    toRet->AdjMatrix.SizeInBytes += (nodesAmountSqr % BITS_IN_BYTES) ? 1 : 0;

    toRet->AdjMatrix.Set = (u_char*)calloc(toRet->AdjMatrix.SizeInBytes,
                                          sizeof(toRet->AdjMatrix.Set[0]));
    assert(toRet->AdjMatrix.Set);

    toRet->Colors = (EColor*)calloc(toRet->NodesAmount,
                                    sizeof(toRet->Colors[0]));
    assert(toRet->Colors);

    toRet->Answer.Array = (unsigned int*)calloc(toRet->NodesAmount,
                                                sizeof(toRet->Answer.Array[0]));
    assert(toRet->Answer.Array);
    return toRet;
}


void AddEdge(TGraph* graph, u_int from, u_int to) {
    assert(from <= graph->NodesAmount && to <= graph->NodesAmount);
    SetBit(graph->AdjMatrix, from * graph->NodesAmount + to);
}

u_char GetPath(TGraph* graph, u_int from, u_int to) {
    assert(from <= graph->NodesAmount && to <= graph->NodesAmount);
    return GetBit(graph->AdjMatrix, from * graph->NodesAmount + to);
}


void FreeGraph(TGraph* g) {
    free(g->AdjMatrix.Set);
    free(g->Colors);
    free(g->Answer.Array);
    free(g);
}


TGraph* ReadGraph() {
    u_int nodesAmount = 0;
    if (scanf("%u", &nodesAmount) != 1) {
        ExitWithError(BadNumberOfLines);
    }
    if (nodesAmount > 2000) {
        ExitWithError(BadNumberOfVertices);
    }
    u_int endgesAmount = 0;
    if (scanf("%u", &endgesAmount) != 1) {
        ExitWithError(BadNumberOfLines);
    }
    if (endgesAmount > nodesAmount * (nodesAmount + 1) / 2) {
        ExitWithError(BadNumberOfEdges);
    }
    TGraph* g = InitGraph(nodesAmount);
    for (size_t i = 0; i < endgesAmount; i++) {
        u_int from = 0;
        u_int to = 0;
        if (scanf("%u %u", &from, &to) != 2) {
            FreeGraph(g);
            ExitWithError(BadNumberOfLines);
        }
        if (from == 0 || to == 0 ||
            from > g->NodesAmount || to > g->NodesAmount) {
            FreeGraph(g);
            ExitWithError(BadVertex);
        }
        AddEdge(g, from - 1, to - 1);
    }
    return g;
}


void PaintBlack(TGraph* g, u_int node_index) {
    g->Colors[node_index] = Black;
}


void PaintGray(TGraph* g, u_int node_index) {
    g->Colors[node_index] = Gray;
}


int IsGray(TGraph* g, u_int node_index) {
    return g->Colors[node_index] == Gray;
}


int IsBlack(TGraph* g, u_int node_index) {
    return g->Colors[node_index] == Black;
}


int IsFullBypass(TGraph* g) {
    return g->NodesAmount == g->Answer.IndexToAppend;
}


int TopDFS(TGraph* g, u_int start) {
    if (IsGray(g, start)) {
        FreeGraph(g);
        ExitWithError(ImpossibleToSort);
    }
    if (IsBlack(g, start)) {
        return EXIT_SUCCESS;
    }
    PaintGray(g, start);
    for (size_t i = 0; i < g->NodesAmount; i++) {
        if (GetPath(g, start, i)) {
            if (i == start) {
                FreeGraph(g);
                ExitWithError(ImpossibleToSort);
            }
            TopDFS(g, i);
        }
    }
    PaintBlack(g, start);
    AddToArray(&g->Answer, start);
    return EXIT_SUCCESS;
}


int TopSort(TGraph* g) {
    for (size_t i = 0; i < g->NodesAmount; i++) {
        TopDFS(g, i);
    }
    if (!IsFullBypass(g)) {
        FreeGraph(g);
        ExitWithError(ImpossibleToSort);
    }
    PrintAnswer(g);
    FreeGraph(g);
    return EXIT_SUCCESS;
}
