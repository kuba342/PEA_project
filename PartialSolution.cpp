#include "PartialSolution.h"



PartialSolution::PartialSolution()
{
	this->destination = INT_MAX;
	this->oneBeforeLast = INT_MAX;
	this->set = new BiList();
	this->nodes = new BiList();
	this->sumOfWeight = 0;
	this->matrix = nullptr;
	this->s = 0;
}

PartialSolution::PartialSolution(AdjMatrix* matrix, int s)
{
	this->destination = INT_MAX;
	this->oneBeforeLast = INT_MAX;
	this->set = new BiList();
	this->nodes = new BiList();
	this->sumOfWeight = 0;
	this->matrix = matrix;
	this->s = s;
}

PartialSolution::~PartialSolution()
{
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

BiList* PartialSolution::getNodes()
{
	return this->nodes;
}


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

