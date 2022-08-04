// Copyright [2022] <Olimpiev Y.>
#include "Exception.h"


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
    exit(EXIT_SUCCESS);
}
