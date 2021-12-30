#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(AdjMatrix* matrix)
{
	this->graph = matrix;
	this->populationSize = 10;
	this->crossingFactor = 0.9;
	this->mutationFactor = 0.9;
	this->iterations = 100;
	this->bestPath = new BiList();
	//Wype³niam najlepsz¹ œcie¿kê zerami
	for (int i = 0; i < graph->getV() - 1; i++) {
		bestPath->addAtTheEnd(0);
	}
	this->bestWeight = INT_MAX;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	delete this->bestPath;
}

void GeneticAlgorithm::calculate()
{
	//TO DO
}

void GeneticAlgorithm::showBestCycle()
{
	std::cout << "Najkrotsza sciezka:\n";
	std::cout << "[ 0 ";
	for (int i = 0; i < bestPath->getCount(); i++) {
		std::cout << bestPath->getElement(i)->key << " ";
	}
	std::cout << "0 ]\n";
	std::cout << "Cost: " << bestWeight << "\n";
}

void GeneticAlgorithm::setPopulationSize(int size)
{
	this->populationSize = size;
}

int GeneticAlgorithm::getPopulationSize()
{
	return this->populationSize;
}

void GeneticAlgorithm::setCrossingFactor(double factor)
{
	this->crossingFactor = factor;
}

double GeneticAlgorithm::getCrossingFactor()
{
	return this->crossingFactor;
}

void GeneticAlgorithm::setMutationFactor(double factor)
{
	this->mutationFactor = factor;
}

double GeneticAlgorithm::getMutationFactor()
{
	return this->mutationFactor;
}

void GeneticAlgorithm::setIterations(int iterations)
{
	this->iterations = iterations;
}

BiList* GeneticAlgorithm::getBestPath()
{
	return this->bestPath;
}

int GeneticAlgorithm::getBestWeight()
{
	return this->bestWeight;
}

void GeneticAlgorithm::generatePopulation()
{

}

double GeneticAlgorithm::drawFromTheRange01()
{
	int number = std::rand() % 10000;
	double random = (double)number / 10000;
	return random;
}

void GeneticAlgorithm::updateBestPath(Individual* individual)
{
	bestWeight = individual->getCost();
	for (int i = 0; i < bestPath->getCount(); i++) {
		bestPath->getElement(i)->key = individual->getPath()->getElement(i)->key;
	}
}
