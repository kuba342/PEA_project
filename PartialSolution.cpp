#include "PartialSolution.h"



PartialSolution::PartialSolution()
{
	this->destination = INT_MAX;
	this->oneBeforeLast = INT_MAX;
	this->set = new BiList();
	//this->nodes = new BiList();
	this->sumOfWeight = INT_MAX;
	this->matrix = nullptr;
	this->s = 0;
	this->previous = nullptr;
}

PartialSolution::PartialSolution(AdjMatrix* matrix, int s)
{
	this->destination = INT_MAX;
	this->oneBeforeLast = INT_MAX;
	this->set = new BiList();
	//this->nodes = new BiList();
	this->sumOfWeight = INT_MAX;
	this->matrix = matrix;
	this->s = s;
	this->previous = nullptr;
}

PartialSolution::~PartialSolution()
{
	delete this->set;
}



//SETTERY I GETTERY
int PartialSolution::getS()
{
	return this->s;
}

int PartialSolution::getDestination()
{
	return this->destination;
}

int PartialSolution::getSumOfWeights()
{
	return this->sumOfWeight;
}

int PartialSolution::getOneBeforeLast()
{
	return this->oneBeforeLast;
}

BiList* PartialSolution::getSet()
{
	return this->set;
}

/*BiList* PartialSolution::getNodes()
{
	return this->nodes;
}*/


//SETTERY
void PartialSolution::setDestination(int destination)
{
	this->destination = destination;
}

void PartialSolution::setSumOfWeights(int sum)
{
	this->sumOfWeight = sum;
}

void PartialSolution::setOneBeforeLast(int OneBefore)
{
	this->oneBeforeLast = OneBefore;
}

void PartialSolution::setPrevious(PartialSolution* previous)
{
	this->previous = previous;
}

void PartialSolution::deleteSet()
{
	delete this->set;
	this->set = new BiList();
}

