#ifndef LIST_H
#define LIST_H

#include "Structures.h"

class BaseSingly {
protected:
    int count;
    Edge* head;
    Edge* current;

public:
    BaseSingly() = default;
    ~BaseSingly() = default;
    virtual void insert_at_front(edgeData& val) = 0;
    virtual void insert_at_end(edgeData& val) = 0;
    virtual void delete_at_front() = 0;
    virtual void delete_at_end() = 0;
    virtual void print() = 0;
    virtual int search(edgeData& val) = 0;
};

class List : public BaseSingly {
public:
    List() = default;
    ~List() = default;
    void insert_at_front(edgeData& val);
    void insert_at_end(edgeData& val);
    void delete_at_front();
    void delete_at_end();
    void print();
    int search(edgeData& val);
    Edge* getHead();
};

#endif // LIST_H
