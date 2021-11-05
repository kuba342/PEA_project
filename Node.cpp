#include "Node.h"

Node::Node() {
    this->color = 'R';
    this->key = 0;
    this->left = 0;
    this->right = 0;
    this->parent = 0;
}

Node::~Node() {

}

//GETTERY
Node* Node::getParent() {
    return this->parent;
}

Node* Node::getLeft() {
    return this->left;
}

Node* Node::getRight() {
    return this->right;
}

int Node::getKey() {
    return this->key;
}

char Node::getColor() {
    return this->color;
}

//SETTERY
void Node::setParent(Node* Parent) {
    this->parent = Parent;
}

void Node::setLeft(Node* leftSon) {
    this->left = leftSon;
}

void Node::setRight(Node* rightSon) {
    this->right = rightSon;
}

void Node::setKey(int Key) {
    this->key = Key;
}

void Node::setColor(char Color) {
    this->color = Color;
}