#include "TSPSimulatedAnnealing.h"


TSPSimulatedAnnealing::TSPSimulatedAnnealing(AdjMatrix* matrix)
{
	this->numberOfCycles = 5;
	this->matrix = matrix;
	this->actualPath = new Array();
	this->actualPathWeight = INT_MAX;
	this->newPath = new Array();
	this->newPathWeight = INT_MAX;
	this->bestPath = new Array();
	this->bestWeight = INT_MAX;

	for (int i = 1; i < matrix->getV(); i++) {
		actualPath->addAtTheEnd(i);
		newPath->addAtTheEnd(i);
		bestPath->addAtTheEnd(i);
	}
	this->coolingFactor = 0.99999;
	this->firstTemp = 50.0;
	this->minimalTemp = 5.0;
	this->currentTemp = this->firstTemp;
	this->iterations = 5;
	this->swapIndex = 0;

	//Start randomizing
	srand(time(NULL));
}

TSPSimulatedAnnealing::~TSPSimulatedAnnealing()
{
	delete this->actualPath;
	delete this->bestPath;
	delete this->newPath;
}

void TSPSimulatedAnnealing::calculate()
{
	for (int x = 0; x < numberOfCycles; x++) {
		renewParameters();
		//W tym miejscu bêdzie g³ówny algorytm:
		//Pierwsze losowe rozwi¹zanie
		determineFirstSolution();
		//Jego koszt
		calculateActualPathWeight();
		//Pierwsze jako aktualnie najlepsze
		if (x == 0) {
			updateBestSolution();
		}
		//Pêtla algorytmu
		while (currentTemp >= minimalTemp) {
			int actualCost = this->bestWeight;
			//max prób poszukiwania
			int max = (matrix->getV() * matrix->getV()) / 2;
			for (int i = 0; i < max; i++) {
				//Nowe rozwi¹zanie:
				nextSolution();
			}
			//Sch³adzanie
			cooling();
		}
	}
}

void TSPSimulatedAnnealing::showBestCycle()
{
	std::cout << "Najkrotsza sciezka:\n";
	std::cout << "[ 0 ";
	for (int i = 0; i < bestPath->getSize(); i++) {
		std::cout << bestPath->getTable()[i] << " ";
	}
	std::cout << "0 ]\n";
	std::cout << "Cost: " << bestWeight << "\n";
}

void TSPSimulatedAnnealing::renewParameters()
{
	this->currentTemp = this->firstTemp;
}

void TSPSimulatedAnnealing::determineFirstSolution()
{
	//Wype³niam zbiór wierzcho³ków
	Array* set = new Array();
	for (int i = 1; i < this->matrix->getV(); i++) {
		set->addAtTheEnd(i);
	}
	//Dla ka¿dego z nieu¿ytych wierzcho³ków:
	for (int i = 1; i < this->matrix->getV(); i++) {
		//Losowy indeks modulo rozmiar
		int index = (std::rand() % set->getSize());
		//Dodajê na koniec wybrany element
		actualPath->getTable()[i - 1] = set->getTable()[index];
		newPath->getTable()[i - 1] = set->getTable()[index];
		//Usuwam ze zbioru wybrany element
		set->removeOnPosition(index);
	}
}

void TSPSimulatedAnnealing::nextSolution()
{
	//Wyznaczam indeks do zamiany w tablicy newPath
	int swapIndex = rand() % (matrix->getV() - 2);
	//Przepisujê actualPath do newPath
	updateNewPath();
	calculateNewPathWeight(swapIndex);
	checkConditions(swapIndex);
}

void TSPSimulatedAnnealing::checkConditions(int index)
{
	if (newPathWeight - actualPathWeight < 0) {
		updateActualPath(index);
		if (actualPathWeight < bestWeight) {
			updateBestSolution();
		}
	}
	else {
		if (drawFromTheRange01() < calculateHeuristic()) {
			updateActualPath(index);
		}
	}
}

void TSPSimulatedAnnealing::updateBestSolution()
{
	this->bestWeight = this->actualPathWeight;
	for (int i = 0; i < this->actualPath->getSize(); i++) {
		bestPath->getTable()[i] = actualPath->getTable()[i];
	}
}

void TSPSimulatedAnnealing::updateActualPath(int index)
{
	this->actualPathWeight = newPathWeight;
	actualPath->swap(index, index + 1);
}

void TSPSimulatedAnnealing::updateNewPath()
{
	for (int i = 0; i < actualPath->getSize(); i++) {
		newPath->getTable()[i] = actualPath->getTable()[i];
	}
	newPathWeight = actualPathWeight;
}

void TSPSimulatedAnnealing::calculateActualPathWeight()
{
	actualPathWeight = 0;
	actualPathWeight += this->matrix->distance(0, actualPath->getTable()[0]);
	for (int i = 0; i < actualPath->getSize() - 1; i++) {
		actualPathWeight += this->matrix->distance(actualPath->getTable()[i], actualPath->getTable()[i+1]);
	}
	actualPathWeight += this->matrix->distance(actualPath->getTable()[actualPath->getSize()-1], 0);
	newPathWeight = actualPathWeight;
}

void TSPSimulatedAnnealing::calculateNewPathWeight(int index)
{
	newPathWeight = actualPathWeight;
	//Odejmujê 3 krawêdzie bior¹ce udzia³ w zamianie
	if (index == 0) {
		newPathWeight -= matrix->distance(0, newPath->getTable()[index]);
	}
	else {
		newPathWeight -= matrix->distance(newPath->getTable()[index - 1], newPath->getTable()[index]);
	}
	newPathWeight -= matrix->distance(newPath->getTable()[index], newPath->getTable()[index + 1]);
	if (index + 1 == actualPath->getSize()-1) {
		newPathWeight -= matrix->distance(newPath->getTable()[index + 1], 0);
	}
	else {
		newPathWeight -= matrix->distance(newPath->getTable()[index + 1], newPath->getTable()[index + 2]);
	}
	//Zamiana
	newPath->swap(index, index + 1);
	//Dodajê do kosztu te 3 nowe krawêdzie
	if (index == 0) {
		newPathWeight += matrix->distance(0, newPath->getTable()[index]);
	}
	else {
		newPathWeight += matrix->distance(newPath->getTable()[index - 1], newPath->getTable()[index]);
	}
	newPathWeight += matrix->distance(newPath->getTable()[index], newPath->getTable()[index + 1]);
	if (index + 1 == actualPath->getSize() - 1) {
		newPathWeight += matrix->distance(newPath->getTable()[index + 1], 0);
	}
	else {
		newPathWeight += matrix->distance(newPath->getTable()[index + 1], newPath->getTable()[index + 2]);
	}
}

double TSPSimulatedAnnealing::calculateHeuristic()
{
	double param = (double)(newPathWeight - actualPathWeight) / currentTemp;
	double result = exp(param);
	return result;
}

void TSPSimulatedAnnealing::cooling()
{
	this->currentTemp = currentTemp * coolingFactor;
}

double TSPSimulatedAnnealing::drawFromTheRange01()
{
	int number = std::rand() % 10000;
	double random = (double)number / 10000;
	return random;
}


void TSPSimulatedAnnealing::setFirstTemp(double temp)
{
	this->firstTemp = temp;
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

void TSPSimulatedAnnealing::setMinimalTemp(double minimalTemp)
{
	this->minimalTemp = minimalTemp;
}

double TSPSimulatedAnnealing::getcurrentTemp()
{
	return this->currentTemp;
}

int TSPSimulatedAnnealing::getIterations()
{
	return this->iterations;
}

double TSPSimulatedAnnealing::getCoolingDactor()
{
	return this->coolingFactor;
}

void TSPSimulatedAnnealing::setCoolingFactor(double coolingFactor)
{
	this->coolingFactor = coolingFactor;
}

void TSPSimulatedAnnealing::setNumberOfCycles(int cycles)
{
	this->numberOfCycles = cycles;
}
