// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
root=nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
if (!n)
    return;
clear(n->left);
clear(n->right);
delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (n -> info > value) {
        if (n -> left == nullptr) {
            n -> left = new Node(value);
            n -> left -> parent = n;
            return true;
        } else {
            return insert(value, n -> left);
        }
    } else if (n -> info < value) {
        if (n -> right == nullptr) {
            n -> right = new Node(value);
            n -> right -> parent = n;
            return true;
        } else {
            return insert(value, n -> right);
        }
    } else {
        return false;
    }
    }

// print tree data pre-order

void IntBST::printPreOrder() const {
    printPreOrder(root);
}

void IntBST::printPreOrder(Node* n) const {

    if (n == nullptr) {
        return;
    }
    cout << n -> info << " ";
    printPreOrder(n -> left);
    printPreOrder(n -> right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
   printInOrder(root);
}

void IntBST::printInOrder(Node* n) const {
    if (n == nullptr) {
        return;
    }
    printInOrder(n -> left);
    cout << n -> info << " ";
    printInOrder(n -> right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node* n) const {
     if (n == nullptr) {
        return;
    }
    printPostOrder(n -> left);
    printPostOrder(n -> right);
    cout << n -> info << " ";
}
// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n==nullptr){
        return 0;
    }
    return n->info+sum(n->left)+sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n==nullptr){
        return 0;
    }
    return 1+count(n->left)+count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return NULL;

    if (value == n->info)
        return n;
    else if (value < n->info)
        return getNodeFor(value, n->left);
    else
        return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
  return getNodeFor(value, root) != NULL;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
  Node* cur = getNodeFor(value, root);
    if (!cur) return NULL;

    if (cur->left) {
        Node* p = cur->left;
        while (p->right)
            p = p->right;
        return p;
    }

    Node* p = cur->parent;
    while (p && cur == p->left) {
        cur = p;
        p = p->parent;
    }
    return p;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
   Node* p = getPredecessorNode(value);
    if (!p) return 0;   // lab 说明：没有 predecessor 返回 0
    return p->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
  Node* cur = getNodeFor(value, root);
    if (!cur) return NULL;

    if (cur->right) {
        Node* p = cur->right;
        while (p->left)
            p = p->left;
        return p;
    }

    Node* p = cur->parent;
    while (p && cur == p->right) {
        cur = p;
        p = p->parent;
    }
    return p;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
 Node* s = getSuccessorNode(value);
    if (!s) return 0;
    return s->info;
}


bool IntBST::remove(int value){
  Node* cur = getNodeFor(value, root);
    if (!cur) return false;

    if (cur->left && cur->right) {
    Node* s = cur->right;
    while (s->left) s = s->left;
    cur->info = s->info;
    cur = s; 
}
    Node* child = cur->left ? cur->left : cur->right;

    if (child)
        child->parent = cur->parent;

    if (!cur->parent) {
        root = child; 
    } else if (cur == cur->parent->left) {
        cur->parent->left = child;
    } else {
        cur->parent->right = child;
    }

    delete cur;
    return true;
}
