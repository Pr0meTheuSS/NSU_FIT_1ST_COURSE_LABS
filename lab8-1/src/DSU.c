// Copyright [2022] <Olimpiev Y.>
#include "DSU.h"


TDSUElement* Find(TDSUElement* element) {
    assert(element);
    if (element->Parent == NULL) {
        return element;
    }
    return element->Parent = Find(element->Parent);
}


int Union(TDSUElement* e1, TDSUElement* e2) {
    TDSUElement* p1 = Find(e1);
    TDSUElement* p2 = Find(e2);
    if (p1 == p2) {
        return EXIT_FAILURE;
    }
    p1->Parent = p2;
    return EXIT_SUCCESS;
}
