#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->firstList = new ListOfPartials();
	this->secondList = new ListOfPartials();
	this->sizeOfSet = 1;
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->firstList = new ListOfPartials();
	this->secondList = new ListOfPartials();
	this->sizeOfSet = 1;
}

HeldKarp::~HeldKarp()
{
}

void HeldKarp::calculate() {
	algorithm();
}

void HeldKarp::showShortestCycle() {

}

void HeldKarp::algorithm()
{
	for (int i = 1; i < this->matrix->getV(); i++) {
		PartialSolution* sol = new PartialSolution(this->matrix, 1);
		sol->setDestination(i);
		sol->setOneBeforeLast(0);
		sol->setSumOfWeights(this->matrix->distance(0,i));
		sol->getSet()->addAtTheEnd(i);
		this->firstList->addAtTheEnd(*sol);
	}

	this->sizeOfSet++;

	for (int i = this->sizeOfSet; i < this->matrix->getV(); i++) {

	}
}
