#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <iostream>
using namespace std;

template<class T>
class baseQueue {
public:
    virtual bool isEmpty() = 0;
    virtual void enqueue(T value) = 0;
    virtual T dequeue() = 0;
    virtual void print() = 0;
    virtual T peek() = 0;
    virtual void makeNull() = 0;
    //virtual Queue<T>* copy() = 0;
};

template<class T>
class Queue : public baseQueue<T> {
private:
    Node<T>* front;
    Node<T>* rear;
    int numOfItems;

public:
    Queue(); 
    ~Queue(); 
    bool isEmpty(); 
    void enqueue(T value); 
    T dequeue(); 
    T peek(); 
    void makeNull(); 
    void print();
    Queue<T>* copy();
    int getCount();
};


template<class T>
int Queue<T>::getCount() {
    return numOfItems;
}

template<class T>
Queue<T>::Queue() {
    this->front = nullptr;
    this->rear = nullptr;
    numOfItems = 0;
}
template<class T>
Queue<T>::~Queue() {
    makeNull();
}

template<class T>
bool Queue<T>::isEmpty() {
    return numOfItems == 0;
}

template<class T>
void Queue<T>::enqueue(T value) {
    Node<T>* newNode = new Node<T>;
    newNode->data = value;
   // cout << "Enqueued : " << newNode->data << endl;
    newNode->next = nullptr;
    if (isEmpty()) {
        this->front = newNode;
        this->rear = newNode;
    }
    else {
        this->rear->next = newNode;
        this->rear = newNode;
    }
    numOfItems++;
}

template<class T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        cout << "Queue is Empty." << endl;
        return T(); 
    }
    Node<T>* temp = front;
    T value = this->front->data;
    this->front = this->front->next;
    delete temp;
    numOfItems--;
    if (numOfItems == 0) {
        this->rear = nullptr;
    }
    return value;
}

template<class T>
T Queue<T>::peek() {
    if (isEmpty()) {
        cout << "Queue is Empty. " << endl;
        return T(); 
    }
    return this->front->data;
}

template<class T>
void Queue<T>::makeNull() {
    while (!isEmpty()) {
        dequeue();
    }
}
template<class T>
void Queue<T>::print() {
    if (isEmpty() == true) {
        cout << "Empty" << endl;
        return;
    }
    while (isEmpty() != true) {
        cout << dequeue() << endl;
    }
}
template<class T>
Queue<T>* Queue<T>::copy() {
    Queue<T>* newQueue = new Queue<T>; 
    Queue<T> tempQueue;
    while (!isEmpty()) {
        T value = dequeue();
        tempQueue.enqueue(value);  
        newQueue->enqueue(value);  
    }
    while (!tempQueue.isEmpty()) {
        enqueue(tempQueue.dequeue());  
    }
    return newQueue; 
}

#endif // QUEUE_H
