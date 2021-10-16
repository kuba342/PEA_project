#include "AdjMatrix.h"
#include <iostream>

AdjMatrix::AdjMatrix(int V)
{
	this->V = V;
	this->matrix = new int* [V];

	for (int i = 0; i < V; i++) {
		this->matrix[i] = new int[V];
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			this->matrix[i][j] = 0;
		}
	}
}

AdjMatrix::~AdjMatrix()
{
	for (int i = 0; i < this->V; i++) {
		delete[] this->matrix[i];
	}
	delete[] this->matrix;
}

bool AdjMatrix::addEdge(int beg, int end, int weight) {
	if ((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)) {
		return false;
	}
	else
	{
		this->matrix[beg][end] = weight;
		this->matrix[end][beg] = weight;
	}
	return true;
}

bool AdjMatrix::addDirectedEdge(int beg, int end, int weight) {
	if ((beg > this->V) || (beg < 0) || (end > this->V) || (end < 0) || (weight < 0)) {
		return false;
	}
	else
	{
		this->matrix[beg][end] = weight;
	}
	return true;
}

void AdjMatrix::showGraph() {
	for (int i = 0; i < this->V; i++) {
		printf("Node %3d: |", i);
		for (int j = 0; j < this->V; j++) {
			if (this->matrix[i][j] < 0) {
				printf("%+5d", matrix[i][j]);
			}
			else {
				printf("%5d", matrix[i][j]);
			}
		}
		printf("   |\n");
	}
}

int AdjMatrix::getV() {
	return this->V;
}

int** AdjMatrix::getMatrix() {
	return this->matrix;
}