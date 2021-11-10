#include "BranchAndBound.h"

BranchAndBound::BranchAndBound(AdjMatrix* matrix)
{
	this->matrix = matrix;
	this->minWeights = new Array();
	this->minValue = 0;
	this->path = new BiList();
	this->unusedNodes = new BiList();
	this->solution = new BnBSolution();
}

BranchAndBound::~BranchAndBound()
{
	delete this->minWeights;
	delete this->path;
	delete this->unusedNodes;
	delete this->solution;
}


void BranchAndBound::calculate() {
	countMinWeights();
	prepare();
	solveByRecursion(this->minValue);
}

BnBSolution* BranchAndBound::getSolution()
{
	return this->solution;
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
	for (int i = 0; i < this->minWeights->getSize();i++) {
		this->minValue += this->minWeights->getTable()[i];
		this->unusedNodes->addAtTheEnd(i);
	}
	this->unusedNodes->removeAtTheBeginning();
	this->path->addAtTheEnd(0);
}

int BranchAndBound::heuristic(int previous, int nextNode)
{
	int result = previous - this->minWeights->getTable()[this->path->getTail()->key] + this->matrix->distance(this->path->getTail()->key, nextNode);
	return result;
}

void BranchAndBound::solveByRecursion(int heur)
{
	//Je�li nie ma ju� nieu�ywanych wierzcho�k�w
	if (this->unusedNodes->getCount() == 0) {
		//Oblicz koszt
		int totalCost = heuristic(heur, 0);
		//I aktualizacja rozwi�zania
		if (totalCost < this->solution->getCost()) {
			updateSolution(totalCost);
		}
	}
	//Iteruj przez nieu�yte wierzcho�ki
	for (int i = 0; i < this->unusedNodes->getCount(); i++) {
		//We� nowy wierzcho�ek
		int currentNode = this->unusedNodes->getHead()->key;
		this->unusedNodes->removeAtTheBeginning();
		//Wyznacz now� heurystyk�
		int newHeuristic = heuristic(heur, currentNode);
		//Je�li mniejsza ni� aktualny koszt rozwi�zania:
		if (newHeuristic < this->solution->getCost()) {
			this->path->addAtTheEnd(currentNode);
			solveByRecursion(newHeuristic);
			this->path->removeAtTheEnd();
		}
		//Usu� z listy nieu�ytych wierzcho�k�w aktualnie przeanalizowany
		this->unusedNodes->addAtTheEnd(currentNode);
	}
}

void BranchAndBound::updateSolution(int cost)
{
	delete this->solution;
	this->solution = new BnBSolution();
	this->solution->setCost(cost);
	for (int i = 0; i < this->path->getCount(); i++) {
		this->solution->getCycle()->addAtTheEnd(this->path->getElement(i)->key);
	}
	this->solution->getCycle()->addAtTheEnd(0);
}





