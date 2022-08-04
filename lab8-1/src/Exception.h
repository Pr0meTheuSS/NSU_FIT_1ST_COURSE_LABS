// Copyright [2022] <Olimpiev Y.>
#pragma once
#include <stdlib.h>
#include <stdio.h>


enum EExitCode {
    ExitSuccess = EXIT_SUCCESS,
    NoSpanningTree,
    BadNumberOfVertices,
    BadNumberOfLines,
    BadNumberOfEdges,
    BadVertex,
    BadLength,
};

typedef enum EExitCode EExitCode;

const char* ErrorMsg(EExitCode e);

void ExitWithError(EExitCode e);
