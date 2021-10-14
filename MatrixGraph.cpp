#include "MatrixGraph.h"
#include <iostream>

MatrixGraph::MatrixGraph(int V, int E) {
    this->V = V;
    this->E = E;
    this->ECount = 0;
    this->sumWeights = 0;
    this->matrix = new int* [V];
    for (int i = 0; i < V; i++) {
        this->matrix[i] = new int[E];
    }
    this->weights = new int[E];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < E; j++) {
            this->matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++) {
        this->weights[i] = 0;
    }
}

MatrixGraph::~MatrixGraph() {
    for (int i = 0; i < this->V; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

bool MatrixGraph::addEdge(int beg, int end, int weight) {
    if ((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)) {
        return false;
    }
    else {
        this->matrix[beg][ECount] = 1;       //Pocz¹tek jako 1
        this->matrix[end][ECount] = 1;       //Koniec jako 1
        this->weights[ECount] = weight;
        ECount++;
        this->sumWeights += weight;
    }
    return true;
}

bool MatrixGraph::addDirectedEdge(int beg, int end, int weight) {
    if ((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)) {
        return false;
    }
    else {
        this->matrix[beg][this->ECount] = 1;       //Pocz¹tek jako 1
        this->matrix[end][this->ECount] = -1;      //Koniec jako -1
        this->weights[this->ECount] = weight;
        this->ECount++;
        this->sumWeights += weight;
    }
    return true;
}

void MatrixGraph::showGraph() {
    for (int i = 0; i < this->V; i++) {
        printf("Node %3d: |", i);
        for (int j = 0; j < this->E; j++) {
            if (this->matrix[i][j] < 0) {
                printf("%+5d", matrix[i][j]);
            }
            else {
                printf("%5d", matrix[i][j]);
            }
        }
        printf("   |\n");
    }

    printf("\nWeights:  |");
    for (int i = 0; i < this->E; i++) {
        printf("%5d", weights[i]);
    }
    printf("   |\n");
}

//Settery i gettery
int** MatrixGraph::getMatrix() {
    return this->matrix;
}

int* MatrixGraph::getWeights() {
    return this->weights;
}

int MatrixGraph::getECount() {
    return this->ECount;
}

int MatrixGraph::getE() {
    return this->E;
}

int MatrixGraph::getV() {
    return this->V;
}

int MatrixGraph::getSumWeights() {
    return this->sumWeights;
}