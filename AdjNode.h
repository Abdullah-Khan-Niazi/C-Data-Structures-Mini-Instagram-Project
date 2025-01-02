#ifndef ADJNODE_H
#define ADJNODE_H
#include"List.h"
struct AdjNode {
    userData data;
    AdjNode* next;
    List* edges;
    int vertexID;

    AdjNode() : vertexID(0), next(nullptr), edges(nullptr) {}
};
#endif // ADJNODE_H