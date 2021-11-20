#include "TSPSimulatedAnnealing.h"

TSPSimulatedAnnealing::TSPSimulatedAnnealing()
{
}

TSPSimulatedAnnealing::TSPSimulatedAnnealing(AdjMatrix* matrix)
{
	this->matrix = matrix;
	this->currentIteration = 0;
	this->actualPath = new Array();
	this->bestPath = new Array();
}

TSPSimulatedAnnealing::~TSPSimulatedAnnealing()
{
	delete this->actualPath;
	delete this->bestPath;
}

void TSPSimulatedAnnealing::prepare()
{

}











void TSPSimulatedAnnealing::setFirstTemp(double temp)
{
	this->firstTemp = temp;
}

void TSPSimulatedAnnealing::setminimalTemp(double temp)
{
	this->minimalTemp = temp;
}

void TSPSimulatedAnnealing::setIterations(int iterations)
{
	this->iterations = iterations;
}

Array* TSPSimulatedAnnealing::getActualPath()
{
	return this->actualPath;
}

Array* TSPSimulatedAnnealing::getBestPath()
{
	return this->bestPath;
}

int TSPSimulatedAnnealing::getBestWeight()
{
	return this->bestWeight;
}

double TSPSimulatedAnnealing::getFirstTemp()
{
	return this->firstTemp;
}

double TSPSimulatedAnnealing::getMinimalTemp()
{
	return this->minimalTemp;
}

double TSPSimulatedAnnealing::getcurrentTemp()
{
	return this->currentTemp;
}

int TSPSimulatedAnnealing::getIterations()
{
	return this->iterations;
}

int TSPSimulatedAnnealing::getCurrentIteration()
{
	return this->currentIteration;
}

double TSPSimulatedAnnealing::getCoolingDactor()
{
	return this->coolingFactor;
}
