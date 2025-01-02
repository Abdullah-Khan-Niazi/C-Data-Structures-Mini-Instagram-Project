#include"List.h"

//BaseSingly::BaseSingly() {
//    count = 0;
//    head = nullptr;
//    current = nullptr;
//}
//
//List::List() {}
//List::~List() {
//    while (count > 0) {
//        delete_at_end();
//    }
//}
void List::insert_at_front(edgeData& val) {
    Edge* temp = new Edge;
    temp->data = val;
    temp->next = head;
    head = temp;
    count++;
}
void List::insert_at_end(edgeData& val) {
    if (head == nullptr) {
        insert_at_front(val);
        return;
    }
    current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    Edge* temp = new Edge;
    temp->data = val;
    current->next = temp;
    count++;
}

void List::delete_at_front() {
    if (head == nullptr) return;
    current = head;
    head = head->next;
    delete current;
    count--;
}
void List::delete_at_end() {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete_at_front();
        return;
    }
    current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    count--;
}
int List::search(edgeData& val) {
    current = head;
    int index = 1;
    while (current != nullptr) {
      /*  if (current->edgeData == val) {
            cout << "Found at Index: " << index << endl;
            return index;
        }*/
        current = current->next;
        index++;
    }
    cout << "Not Found" << endl;
    return -1;
}
void List::print() {
    current = head;
    if (current == nullptr) {
        cout << "[No Friends]";
    }
    while (current != nullptr) {
        cout << "[" << current->data << "]";
        current = current->next;
    }
    cout << endl;
}
Edge* List::getHead() {
    return head;
}