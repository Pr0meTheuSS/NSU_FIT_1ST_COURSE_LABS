  // "Copyright [2022] <Olimpiev Y.>"
#pragma once
#include <stdio.h>  // for printf with error-string
#include <stdlib.h>  // for func exit()


enum EExitCode {
  NoSpanningTree,
  BadNumberOfVertices,
  BadNumberOfLines,
  BadNumberOfEdges,
  BadVertex,
  BadLength
};

typedef enum EExitCode EExitCode;

const char* ErrorMsg(EExitCode e);

void ExitWithError(EExitCode e);
