// "Copyright [2022] <Olimpiev Y.>"
#pragma once
#define pass
#define true 1
#define false 0
#define const_spec_str_node_index_type "%u"

typedef struct TEdge TEdge;
typedef struct TGraph TGraph;

typedef struct TPriorityQueueNode TPriorityQueueNode;
typedef struct TPriorityQueue TPriorityQueue;

typedef unsigned char bool;
typedef unsigned int ui;

typedef ui TEdgeWeightType;
typedef ui TNodeIndexType;

TNodeIndexType max(TNodeIndexType x, TNodeIndexType y);

TNodeIndexType min(TNodeIndexType x, TNodeIndexType y);

TNodeIndexType GetCellNumber(TNodeIndexType x, TNodeIndexType y);
