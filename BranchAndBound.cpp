#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(AdjMatrix* matrix)
{
	this->matrix = matrix;
	this->minWeights = new Array();
	this->minValue = 0;
	this->path = new BiList();
	this->unusedNodes = new BiList();
}

BranchAndBound::~BranchAndBound()
{
}


void BranchAndBound::calculate() {
	countMinWeights();
	prepare();
}

void BranchAndBound::countMinWeights()
{
	for (int i = 0; i < this->matrix->getV(); i++) {
		this->minWeights->addOnPosition(INT_MAX, i);
		for (int j = 0; j < this->matrix->getV(); j++) {
			if (this->minWeights->getTable()[i] > this->matrix->distance(i, j) && i != j) {
				this->minWeights->getTable()[i] = this->matrix->distance(i, j);
			}
		}
	}
}

void BranchAndBound::prepare()
{
	for (int i = 0; i < this->minWeights->getSize(); i++) {
		this->minValue = this->minWeights->getTable()[i];
		this->unusedNodes->addAtTheEnd(i);
	}
	this->unusedNodes->removeAtTheEnd();
	this->path->addAtTheEnd(0);
}

int BranchAndBound::heuristic(int previous, int nextNode)
{
	int result = previous - this->minWeights->getTable()[this->path->getTail()->key] + this->matrix->distance(this->path->getTail()->key, nextNode);
	return result;
}




