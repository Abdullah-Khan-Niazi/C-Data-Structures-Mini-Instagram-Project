#include "Graph.h"
#include "Structures.h"

AdjList::AdjList() : head(nullptr), current(nullptr), vertexCount(0) {
    obj = new Bst<string>;
}

void AdjList::insertVertex(userData val) {
    AdjNode* newVertex = new AdjNode;
    newVertex->data = val;
    newVertex->vertexID = vertexCount++;
    obj->insert(newVertex);
    map.insert(newVertex->vertexID, newVertex->data.username, newVertex->data.password,newVertex);
    newVertex->edges = new List; 
    if (head == nullptr) {
        head = newVertex;
    }
    else {
        current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newVertex;
    }
}

void AdjList::insertAtVertex(int vertex, edgeData val) {
    current = head;
    while (current != nullptr && current->vertexID != vertex) {
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Vertex# " << vertex << " Not Found!" << endl;
        return;
    }
    current->edges->insert_at_end(val); 
}

void AdjList::deleteVertex(string vertex) {
    if (head == nullptr) return;
    if (head->data.username == vertex) {
        AdjNode* temp = head;
        head = head->next;
        delete temp->edges; 
        delete temp;
        return;
    }

    current = head;
    while (current->next != nullptr && current->next->data.username != vertex) {
        current = current->next;
    }
    if (current->next != nullptr) {
        AdjNode* temp = current->next;
        current->next = current->next->next;
        delete temp->edges;  
        delete temp;
    }
    obj->deleteNode(vertex);
}

AdjNode* AdjList::findVertex(int id) {
    return map.getUser(id);
}

//AdjNode* AdjList::findVertex(string username) {
//    current = head;
//    while (current != nullptr) {
//        if (current->data.username == username) return current;
//        current = current->next;
//    }
//    return nullptr;
//}
AdjNode* AdjList::findVertex(string username) {
    AdjNode* result = obj->findNode(username);
    return result;
}

AdjList::~AdjList() {
    while (head != nullptr) {
        AdjNode* temp = head;
        head = head->next;
        delete temp->edges;  
        delete temp;
    }
}
AdjNode* AdjList::getFirstNode() {
    return head;
}
void AdjList::print() {
    current = head;
    cout << "[Graph]" << endl;
    while (current != nullptr) {
        cout << "[" << current->data;
        current->edges->print();
        current = current->next;
    }

    cout << endl << "[TREE]" << endl;
    cout << "[InOrder] : "; obj->printInOrder();
    cout << endl;

    cout << "[HASHMAP]" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "[INDEX] : (USERNAME : PASSWORD)" << endl;
    cout << "-----------------------------------------" << endl;
    map.display();
}
void AdjList::printNames() {
    current = head;
    cout << "-----------------------------" << endl;
    cout << "[ID] \t[USERNAME]" << endl;
    cout << "-----------------------------" << endl;
    while (current != nullptr) {
        cout << "[" << current->vertexID << "] ->  [" << current->data.username << "]" << endl;
        current = current->next;
    }
}
