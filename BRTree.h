#pragma once
#ifndef BRTree_h
#define BRTree_h

#include "Node.h"
#include <iostream>

class BRTree
{
private:
    Node* NIL;
    Node* root;
    int size;

public:
    BRTree();
    ~BRTree();
    void inorderTreeWalk(Node* node);
    Node* treeSearch(Node* node, int k);
    Node* treeMinimum(Node* node);
    Node* treeMaximum(Node* node);
    Node* treeSuccessor(Node* node);
    Node* treePredecessor(Node* node);
    void treeInsert(Node* input);
    void treeDelete(Node* out);
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void addElement(int value);
    void deleteElement(int value);

    //GETTERY
    Node* getRoot();
    int getSize();
    Node* getNIL();
    //SETTERY
    void setRoot(Node* Root);
    //void setSize(int Size);
};

#endif // !BRTree_h
