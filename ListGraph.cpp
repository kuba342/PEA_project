#include "ListGraph.h"
#include <iostream>

ListGraph::ListGraph(int V) {
    this->V = V;
    this->E = 0;
    this->table = new BiList * [V];
    for (int i = 0; i < V; i++) {
        this->table[i] = new BiList();
    }
    this->sumWeights = 0;
}

ListGraph::~ListGraph() {
    for (int i = 0; i < this->V; i++) {
        delete table[i];
    }
    delete[] table;
}

bool ListGraph::addEdge(int beg, int end, int weight) {
    if ((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)) {
        return false;
    }
    else {
        this->table[beg]->addAtTheEnd(end, weight);
        this->table[end]->addAtTheEnd(beg, weight);
        this->E++;
        this->sumWeights += weight;
    }
    return true;
}

bool ListGraph::addDirectedEdge(int beg, int end, int weight) {
    if ((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)) {
        return false;
    }
    else {
        this->table[beg]->addAtTheEnd(end, weight);
        this->E++;
        this->sumWeights += weight;
    }
    return true;
}

void ListGraph::showGraph() {
    for (int i = 0; i < this->V; i++) {
        std::cout << "Node " << i << " ";
        this->table[i]->showList();
        std::cout << "\n";
    }
}

//Settery i gettery
BiList* ListGraph::getListFromArray(int indeks) {
    if (indeks > this->V || indeks < 0) {
        return nullptr;
    }
    else {
        return this->table[indeks];
    }
}

int ListGraph::getE() {
    return this->E;
}

int ListGraph::getV() {
    return this->V;
}

int ListGraph::getSumWeights() {
    return this->sumWeights;
}