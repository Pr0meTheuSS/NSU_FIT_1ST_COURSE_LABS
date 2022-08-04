// Copyright [2022] <Olimpiev Y.>
#pragma once
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
struct TDSUElement {
    struct TDSUElement* Parent;
    NodeIndexType Value;
};

typedef struct TDSUElement TDSUElement;

TDSUElement* Find(TDSUElement* element);

int Union(TDSUElement* e1, TDSUElement* e2);
