#include "TSPSimulatedAnnealing.h"


TSPSimulatedAnnealing::TSPSimulatedAnnealing(AdjMatrix* matrix)
{
	this->matrix = matrix;
	this->actualPath = new Array();
	this->actualPathWeight = INT_MAX;
	this->bestPath = new Array();
	this->bestWeight = INT_MAX;

	this->firstTemp = 1000.0;
	this->minimalTemp = 50.0;
	this->currentTemp = this->firstTemp;
	this->iterations = 10000;
	this->currentIteration = 0;
}

TSPSimulatedAnnealing::~TSPSimulatedAnnealing()
{
	delete this->actualPath;
	delete this->bestPath;
}

void TSPSimulatedAnnealing::prepare()
{

}

void TSPSimulatedAnnealing::determineFirstSolution()
{

}

void TSPSimulatedAnnealing::calculateActualPathWeight()
{
	actualPathWeight = 0;
	actualPathWeight += this->matrix->distance(0, actualPath->getTable()[0]);
	for (int i = 0; i < actualPath->getSize() - 1; i++) {
		actualPathWeight += this->matrix->distance(actualPath->getTable()[i], actualPath->getTable()[i+1]);
	}
	actualPathWeight += this->matrix->distance(actualPath->getTable()[actualPath->getSize()-1], 0);
}

double TSPSimulatedAnnealing::calculateHeuristic()
{
	double param = (actualPathWeight - bestWeight) / currentTemp;
	return exp(param);
}

void TSPSimulatedAnnealing::cooling()
{
	this->currentTemp = currentTemp * coolingFactor;
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

int TSPSimulatedAnnealing::getActualPathWeight()
{
	return this->actualPathWeight;
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
