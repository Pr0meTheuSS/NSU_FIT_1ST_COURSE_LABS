// Copyright [2022] <Olimpiev Y.>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#include "Graph.h"
#include "Kruskal.h"

int main(void) {
    TGraph* graph = ReadGraph(stdin);
    int retCode = KruskalMinSpanningTree(*graph, stdout);
    FreeGraph(graph);
    free(graph);
    if (retCode != EXIT_SUCCESS) {
        ExitWithError((EExitCode)retCode);
    } else {
        return EXIT_SUCCESS;
    }
}
