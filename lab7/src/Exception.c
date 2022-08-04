// "Copyright [2022] Y.Olimpiev"
#include "Exception.h"


void ExitWithError(eExitStatus e) {
    switch (e) {
    case BadNumberOfLines:
        printf("bad number of lines");
        exit(EXIT_SUCCESS);
    case BadNumberOfVertices:
        printf("bad number of vertices");
        exit(EXIT_SUCCESS);
    case BadNumberOfEdges:
        printf("bad number of edges");
        exit(EXIT_SUCCESS);
    case BadVertex:
        printf("bad vertex");
        exit(EXIT_SUCCESS);
    case ImpossibleToSort:
        printf("impossible to sort");
        exit(EXIT_SUCCESS);
    default:
        exit(EXIT_SUCCESS);
    }
}
