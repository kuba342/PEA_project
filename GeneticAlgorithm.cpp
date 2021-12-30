#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(AdjMatrix* matrix)
{
	this->population = nullptr;
	this->parents = nullptr;
	this->children = nullptr;
	this->graph = matrix;
	this->populationSize = 10;		//Ten parametr bêdzie tak¿e liczb¹ rodziców
	this->tournamentParticipants = populationSize / 4;		//¯eby nie braæ wszystkich
	this->crossingFactor = 0.9;
	this->mutationFactor = 0.9;
	this->iterations = 1;
	this->bestPath = new BiList();
	//Wype³niam najlepsz¹ œcie¿kê zerami
	for (int i = 0; i < graph->getV() - 1; i++) {
		bestPath->addAtTheEnd(0);
	}
	this->bestWeight = INT_MAX;
	//Start randomizing
	srand(time(NULL));
}

GeneticAlgorithm::~GeneticAlgorithm()
{
	delete this->bestPath;
}

void GeneticAlgorithm::calculate()
{
	//Wybór populacji pocz¹tkowej (rodziców)
	//Ocena przystosowania chromosomów
	generatePopulation();
	//Pêtla - sprawdzenie warunku zatrzymania
	for (int x = 0; x < iterations; x++) {
		//a. selekcja chromosomów do populacji macierzystej:
		chooseParents();
	}
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

void GeneticAlgorithm::chooseParents()
{
	if (parents != nullptr) {
		delete parents;
	}
	parents = new ListOfIndividuals();
	//Wybieram populationSize rodziców
	for (int i = 0; i < populationSize; i++) {
		//Zbiór indeksów osobników do wylosowania w turnieju
		BiList* set = new BiList();
		//Wype³niam ten zbiór
		for (int j = 0; j < population->getSize(); j++) {
			set->addAtTheEnd(j);
		}
		//Wybieram tournamentParticipants indeksów i zapamiêtujê ten najlepszy
		int bestIndex = 0;
		int bestCost = INT_MAX;
		for (int j = 0; j < tournamentParticipants; j++) {
			//Losujê pozycjê ze zbioru
			int setIndex = (std::rand() % set->getCount());
			//Wybór - indeks w populacji
			int index = set->getElement(setIndex)->key;
			//usuwam ze zbioru indeksów
			set->removeOnPosition(set->getElement(setIndex));
			//Sprawdzam czy aktualnie najlepszy:
			if (population->getElement(index)->individual->getCost() < bestCost) {
				bestIndex = index;
				bestCost = population->getElement(index)->individual->getCost();
			}
		}
		//W tym momencie mam zwyciêzcê turnieju, zatem dodajê go do populacji rodziców
		Individual* ind = population->getElement(bestIndex)->individual;
		//ind->getPath()->showList();
		//std::cout << "\nCost = " << ind->getCost();
		parents->addAtTheEnd(ind);
		//I usuwam z populacji
		population->removeOnPosition(bestIndex);
	}
}

void GeneticAlgorithm::generatePopulation()
{
	this->population = new ListOfIndividuals();
	//Nowa pusta populacja
	for (int i = 0; i < populationSize*2; i++) {
		Individual* ind = new Individual(this->graph->getV() - 1);
		population->addAtTheEnd(ind);
	}
	//Losowanie wartoœci dla populacji:
	for (int i = 0; i < populationSize*2; i++) {
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
		//population->getElement(i)->individual->getPath()->showList();
		//std::cout << " " << population->getElement(i)->individual->getCost() << " \n";
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
