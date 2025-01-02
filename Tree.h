#ifndef TREE_H
#define TREE_H
#include<iostream>
#include"AdjNode.h"
#include <algorithm>
using namespace std;
template<class T>
struct NodeTree {
	T data;
	AdjNode* user;
	NodeTree* left;
	NodeTree* right;
	NodeTree(T val);
};
template<class T>
class Base {
protected:
	NodeTree<T>* root;
public:
	Base();
	virtual void insert(AdjNode* obj) = 0;
	virtual void printInOrder() = 0;
	virtual void deleteNode(T val) = 0;
	virtual AdjNode* findNode(T val) = 0;
};
template<class T>
class Bst :public Base<T> {
public:
	Bst();
	void insert(AdjNode* obj);
	void printInOrder();
	void deleteNode(T val);
	AdjNode* findNode(T val);
private:
	//T max(T a, T b);
	int getHeight(NodeTree<T>* temp);
	int calculateBF(NodeTree<T>* temp);
	void rotateRight(NodeTree<T>*& temp);
	void rotateLeft(NodeTree<T>*& temp);
	void rotateLeftRight(NodeTree<T>*& temp);
	void rotateRightLeft(NodeTree<T>*& temp);
	void insertDataHelper(AdjNode* obj,T val, NodeTree<T>*& temp);
	void deleteNodeHelper(T val, NodeTree<T>*& temp);
	void inOrderHelper(NodeTree<T>* temp);
	AdjNode* findNodeHelper(T val,NodeTree<T>* temp);
};

template<class T>
NodeTree<T>::NodeTree(T val) {
	data = val;
	left = nullptr;
	right = nullptr;
	user = nullptr;
}
template<class T>
Base<T>::Base() {
	root = nullptr;
}
template<class T>
Bst<T>::Bst(){}
template<class T>
void Bst<T>::insert(AdjNode* obj) {
	insertDataHelper(obj, obj->data.username, this->root);
}
template<class T>
void Bst<T>::printInOrder() {
	inOrderHelper(this->root);
	cout << endl;
}
template<class T>
void Bst<T>::deleteNode(T val) {
	deleteNodeHelper(val, this->root);
}
//template<class T>
//T Bst<T>::max(T a, T b) {
//	if (a > b) {
//		return a;
//	}
//	return b;
//}
template<class T>
int Bst<T>::getHeight(NodeTree<T>* temp) {
	if (temp == nullptr) {
		return -1;
	}
	return 1 + std::max(getHeight(temp->left), getHeight(temp->right));
}
template<class T>
int Bst<T>::calculateBF(NodeTree<T>* temp) {
	int leftHeight = getHeight(temp->left);
	int rightHeight = getHeight(temp->right);
	return leftHeight - rightHeight;
}
template<class T>
void Bst<T>::rotateRight(NodeTree<T>*& temp) {
	NodeTree<T>* ptr = temp->left; 
	if (ptr == nullptr) {
		return; 
	}
	temp->left = ptr->right;
	ptr->right = temp;       
	temp = ptr;             
}
template<class T>
void Bst<T>::rotateLeft(NodeTree<T>*& temp) {
	NodeTree<T>* ptr = temp->right; 
	if (ptr == nullptr) {
		return; 
	}
	temp->right = ptr->left; 
	ptr->left = temp;    
	temp = ptr;              
}
template<class T>
void Bst<T>::rotateLeftRight(NodeTree<T>*& temp) {
	if (temp->left == nullptr) {
		return; 
	}
	rotateLeft(temp->left); 
	rotateRight(temp); 
}
template<class T>
void Bst<T>::rotateRightLeft(NodeTree<T>*& temp) {
	if (temp->right == nullptr) {
		return;
	}
	rotateRight(temp->right); 
	rotateLeft(temp);       
}

template<class T>
void Bst<T>::insertDataHelper(AdjNode* obj, T val, NodeTree<T>*& temp) {
	if (temp == nullptr) {
		temp = new NodeTree<T>(val);
		temp->user = obj;
		return;
	}
	if (val < temp->data) {
		insertDataHelper(obj, val, temp->left);
	}
	else if (val > temp->data) {
		insertDataHelper(obj, val, temp->right);
	}
	else {
		return; 
	}
	int bf = calculateBF(temp);
	if (bf > 1) {
		if (val < temp->left->data) {
			rotateRight(temp);
		}
		else {
			rotateLeftRight(temp);
		}
	}
	else if (bf < -1) {
		if (val > temp->right->data) {
			rotateLeft(temp);
		}
		else {
			rotateRightLeft(temp);
		}
	}
}
template<class T>
void Bst<T>::deleteNodeHelper(T val, NodeTree<T>*& temp) {
	if (temp == nullptr) {
		return;
	}
	if (val < temp->data) {
		deleteNodeHelper(val, temp->left);
	}
	else if (val > temp->data) {
		deleteNodeHelper(val, temp->right);
	}
	else {
		if (temp->left == nullptr && temp->right == nullptr) {
			delete temp;
			temp = nullptr;
		}
		else if (temp->left == nullptr) {
			NodeTree<T>* toDelete = temp;
			temp = temp->right;
			delete toDelete;
		}
		else if (temp->right == nullptr) {
			NodeTree<T>* toDelete = temp;
			temp = temp->left;
			delete toDelete;
		}
		else {
			NodeTree<T>* successor = temp->right;
			while (successor->left != nullptr) {
				successor = successor->left;
			}
			temp->data = successor->data;
			temp->user = successor->user;
			deleteNodeHelper(successor->data, temp->right);
		}
	}
	if (temp == nullptr) return;
	int bf = calculateBF(temp);
	if (bf > 1) {
		if (calculateBF(temp->left) >= 0) {
			rotateRight(temp);
		}
		else {
			rotateLeftRight(temp);
		}
	}
	else if (bf < -1) {
		if (calculateBF(temp->right) <= 0) {
			rotateLeft(temp);
		}
		else {
			rotateRightLeft(temp);
		}
	}
}
template<class T>
void Bst<T>::inOrderHelper(NodeTree<T>* temp) {
	if (temp != nullptr) {
		inOrderHelper(temp->left);
		cout << "[" << temp->data << "] ";
		inOrderHelper(temp->right);
	}
}
template<class T>
AdjNode* Bst<T>::findNodeHelper(T val, NodeTree<T>* temp) {
	if (temp == nullptr) {
		return nullptr; // Base case: value not found
	}
	if (temp->user->data.username == val) {
		return temp->user; // Found the node
	}
	// Check left and right subtrees
	AdjNode* leftResult = findNodeHelper(val, temp->left);
	if (leftResult != nullptr) {
		return leftResult; // Found in the left subtree
	}
	return findNodeHelper(val, temp->right); // Continue searching in the right subtree
}

template<class T>
AdjNode* Bst<T>::findNode(T val) {
	return findNodeHelper(val, this->root);
}
#endif // TREE_H
