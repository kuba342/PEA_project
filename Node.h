#pragma once
#ifndef Node_h
#define Node_h

class Node
{
private:
    Node* parent;
    Node* left;
    Node* right;
    int key;
    char color;

public:
    Node();
    ~Node();

    //GETTERY
    Node* getParent();
    Node* getLeft();
    Node* getRight();
    int getKey();
    char getColor();

    //SETTERY
    void setParent(Node* Parent);
    void setLeft(Node* leftSon);
    void setRight(Node* rightSon);
    void setKey(int Key);
    void setColor(char Color);
};

#endif // !Node_h
