#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(AdjMatrix* matrix)
{
	this->population = nullptr;
	this->graph = matrix;
	this->populationSize = 20;
	this->parentalPopulationSize = populationSize / 2;
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
	generatePopulation();
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
	//this->population = new Individual * [populationSize];
	this->population = new ListOfIndividuals();
	//Nowa pusta populacja
	for (int i = 0; i < populationSize; i++) {
		//population[i] = new Individual(this->graph->getV()-1);
		Individual* ind = new Individual(this->graph->getV() - 1);
		population->addAtTheEnd(ind);
	}
	//Losowanie wartoœci dla populacji:
	for (int i = 0; i < populationSize; i++) {
		//Wype³niam zbiór wierzcho³ków
		Array* set = new Array();
		for (int j = 1; j < graph->getV(); j++) {
			set->addAtTheEnd(j);
		}
		//Dla ka¿dego z nieu¿ytych wierzcho³ków:
		for (int j = 1; j < graph->getV(); j++) {
			//losowy indeks modulo rozmiar
			int index = (std::rand() % set->getSize());
			//Dodajê na koniec wybrany element
			//population[i]->getPath()->getElement(j-1)->key = set->getTable()[index];
			population->getElement(i)->individual->getPath()->getElement(j - 1)->key = set->getTable()[index];
			//Usuwam ze zbioru wybrany element
			set->removeOnPosition(index);
		}
		delete set;
		calculateCost(population->getElement(i)->individual);
		//Aktualnie najlepsze rozwi¹zanie
		if (population->getElement(i)->individual->getCost() < bestWeight) {
			updateBestPath(population->getElement(i)->individual);
		}
		population->getElement(i)->individual->getPath()->showList();
		std::cout << " " << population->getElement(i)->individual->getCost() << " \n";
	}
	showBestCycle();
}

void GeneticAlgorithm::calculateCost(Individual* individual)
{
	int cost = 0;
	cost += graph->distance(0, individual->getPath()->getElement(0)->key);
	for (int i = 0; i < individual->getSize() - 1; i++) {
		cost += graph->distance(individual->getPath()->getElement(i)->key, individual->getPath()->getElement(i+1)->key);
	}
	cost += graph->distance(individual->getSize()-1, 0);
	//Ustawiam koszt w obiekcie
	individual->setCost(cost);
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
