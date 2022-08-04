// "Copyright [2022] <Olimpiev Y.>"
#include "Service.h"


TNodeIndexType max(TNodeIndexType x, TNodeIndexType y) {
  return (x > y) ? x : y;
}

TNodeIndexType min(TNodeIndexType x, TNodeIndexType y) {
  return (x > y) ? y : x;
}

TNodeIndexType GetCellNumber(TNodeIndexType x, TNodeIndexType y) {
  // Cantor's numbering for iteartion in AdjMatrix :D
  return ((x + y) * (x + y) + 3 * x + y) / 2;
}
