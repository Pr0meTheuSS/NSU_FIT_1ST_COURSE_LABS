// "Copyright [2022] Y.Olimpiev"
#pragma once
#include <stdio.h>
#include <stdlib.h>


typedef enum eExitStatus {
    BadNumberOfEdges,
    BadNumberOfLines,
    BadNumberOfVertices,
    BadVertex,
    ImpossibleToSort,
} eExitStatus;

void ExitWithError(eExitStatus e);
