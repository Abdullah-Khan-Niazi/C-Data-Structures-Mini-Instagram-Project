#ifndef ADJLIST_H
#define ADJLIST_H

#include "Structures.h"
#include"Tree.h"
#include"AdjNode.h"
#include"HashMap.h"
class baseAdjList {
public:
    virtual void insertVertex(userData val) = 0;
    virtual void insertAtVertex(int vertex, edgeData val) = 0;
    virtual void deleteVertex(string vertex) = 0;
    virtual AdjNode* findVertex(string username) = 0;
    virtual AdjNode* findVertex(int id) = 0;
    virtual AdjNode* getFirstNode() = 0;
};

class AdjList : public baseAdjList {
private:
    Bst<string>*obj;
    AdjNode* head;
    AdjNode* current;
    HashTable map;
    int vertexCount;
public:
    AdjList();
    ~AdjList();
    void insertVertex(userData val);
    void insertAtVertex(int vertex, edgeData val);
    void deleteVertex(string vertex);
    AdjNode* findVertex(string username);
    AdjNode* findVertex(int id);
    AdjNode* getFirstNode();
    void print();
    void printNames();

};

#endif // ADJLIST_H
