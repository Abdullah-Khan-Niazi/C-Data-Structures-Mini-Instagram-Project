#include <iostream>
#include <vector>
#include <string>
#include"AdjNode.h"
using namespace std;

const int TABLE_SIZE = 10; 
struct HashNode {
    int id;           
    string username;
    string password;
    HashNode* next;  
    AdjNode* user;
    HashNode() :id(0), username(""), password(""), next(nullptr), user(nullptr) {};
    HashNode(int ID, string u,string p,AdjNode * t) :id(ID), username(u), password(p), next(nullptr), user(t) {};
};

class HashTable {
private:
    vector<HashNode*> table;
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += static_cast<int>(ch); 
        }
        return hash % TABLE_SIZE;
    }
public:
    HashTable() : table(TABLE_SIZE, nullptr) {}
    void insert(int id, const string& username, const string& password, AdjNode* adjNode = nullptr) {
        int index = hashFunction(username);
        HashNode* newNode = new HashNode(id, username, password, adjNode);
        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            HashNode* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    string getPassword(const string& username) {
        int index = hashFunction(username);
        HashNode* current = table[index];
        while (current != nullptr) {
            if (current->username == username) {
                return current->password;
            }
            current = current->next;
        }
        return "User not found!";
    }
    AdjNode* getUser(int ID) {
        for (int i = 0; i < TABLE_SIZE; i++) { 
            HashNode* current = table[i];
            while (current != nullptr) { 
                if (current->id == ID) {
                    return current->user; 
                }
                current = current->next;
            }
        }
        return nullptr; 
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
                cout << "[" << current->id << "] -> (" << current->username << " : " << current->password << ") ";
                current = current->next;
            }
            cout << endl;
        }
    }
    ~HashTable() {
        for (auto& node : table) {
            while (node != nullptr) {
                HashNode* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }
};

