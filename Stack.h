
#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>
using namespace std;

template<class T>
class baseStack {
protected:
    Node<T>* top;
public:
    virtual bool isEmpty() = 0;
    virtual void push(T val) = 0;
    virtual T pop() = 0;
    virtual T Top() = 0;
    virtual void print() = 0;
   // virtual Stack<T>* copy() = 0;
};

template<class T>
class Stack : public baseStack<T> {
public:
    Stack();
    ~Stack();
    bool isEmpty();
    void push(T val);
    T pop();
    T Top();
    void print();
    Stack<T>* copy();
};

// Constructor definition for Stack
template<class T>
Stack<T>::Stack() {
    this->top = nullptr;
}

// Destructor definition for Stack
template<class T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// isEmpty definition for Stack
template<class T>
bool Stack<T>::isEmpty() {
    return this->top == nullptr;
}

// push definition for Stack
template<class T>
void Stack<T>::push(T val) {
    Node<T>* temp = new Node<T>;
    temp->data = val;
    //cout << "Pushed Data : " << temp->data << endl;
    temp->next = this->top;
    this->top = temp;
}

// pop definition for Stack
template<class T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty.");
    }
    Node<T>* temp = this->top;
    T obj = this->top->data;
    this->top = this->top->next;
    delete temp;
    return obj;
}

// Top definition for Stack
template<class T>
T Stack<T>::Top() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty.");
    }
    return this->top->data;
}

// print definition for Stack
template<class T>
void Stack<T>::print() {
    Node<T>* tempNode = this->top;
    while (tempNode != nullptr) {
        cout << tempNode->data;
        tempNode = tempNode->next;
    }
    cout << endl;
}
template<class T>
Stack<T>* Stack<T>::copy() {
    Stack<T>* temp = new Stack<T>;
    Stack<T> reverse;
    while (!isEmpty()) {
        T obj = pop();
        reverse.push(obj);
    }
    while (!reverse.isEmpty()) {
        T obj = reverse.pop();
        temp->push(obj);
    }
    return temp;
}

#endif // STACK_H
