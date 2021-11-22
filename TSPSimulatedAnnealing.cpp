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

	this->firstTemp = 50000.0;
	this->minimalTemp = 20.0;
	this->currentTemp = this->firstTemp;
	this->iterations = 100;
	this->currentIteration = 0;

	//Start randomizing
	srand(time(NULL));
}

TSPSimulatedAnnealing::~TSPSimulatedAnnealing()
{
	delete this->actualPath;
	delete this->bestPath;
}

void TSPSimulatedAnnealing::calculate()
{
	for (int x = 0; x < numberOfCycles; x++) {
		renewParameters();
		std::cout << "x = " << x << "\n";
		//W tym miejscu bêdzie g³ówny algorytm:
		//Pierwsze losowe rozwi¹zanie
		if (x > 0) {
			delete this->actualPath;
			actualPath = new Array();
		}
		determineFirstSolution();
		//Jego koszt
		calculateActualPathWeight();
		//Pierwsze jako aktualnie najlepsze
		if (x == 0) {
			updateBestSolution();
		}
		//Pêtla algorytmu
		while (/*currentIteration < iterations && */currentTemp >= minimalTemp) {
			int actualCost = this->bestWeight;
			int inneriterator = 0;
			do {
				//L prób poszukiwania
				for (int i = 0; i < matrix->getV(); i++) {
					//Nowe rozwi¹zanie:
					nextSolution();
					//Jego koszt
					calculateNewPathWeight();
					//Sprawdzenie warunków i aktualizacja rozwi¹zañ
					checkConditions();
				}
				inneriterator++;
			} while (actualCost - bestWeight < 0 && inneriterator < iterations);
			//Sch³adzanie
			cooling();
			//Inkrementacja iteracji
			//currentIteration++;
		}
		this->bestPath->showArray();
		std::cout << "Aktualny koszt: " << this->bestWeight << "\n";
	}
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
		this->actualPath->addAtTheEnd(set->getTable()[index]);
		//this->bestPath->addAtTheEnd(set->getTable()[index]);
		//Usuwam ze zbioru wybrany element
		set->removeOnPosition(index);
	}
}

void TSPSimulatedAnnealing::nextSolution()
{
	//Wyznaczam indeks do zamiany w tablicy actualPath
	int swapIndex = rand() % (matrix->getV() - 2);
	//Przepisujê actualPath do newPath
	this->newPathWeight = actualPathWeight;
	delete this->newPath;
	this->newPath = new Array();
	for (int i = 0; i < actualPath->getSize(); i++) {
		newPath->addAtTheEnd(actualPath->getTable()[i]);
	}
	//Zamieniam zawsze 2 s¹siednie ze sob¹
	newPath->swap(swapIndex, swapIndex + 1);
}

void TSPSimulatedAnnealing::checkConditions()
{
	calculateNewPathWeight();
	if (newPathWeight - actualPathWeight < 0) {
		//updateBestSolution();
		updateActualPath();
		if (actualPathWeight < bestWeight) {
			updateBestSolution();
		}
	}
	else {
		if (drawFromTheRange01() < calculateHeuristic()) {
			//updateBestSolution();
			updateActualPath();
		}
	}
}

void TSPSimulatedAnnealing::updateBestSolution()
{
	this->bestWeight = this->actualPathWeight;
	delete this->bestPath;
	this->bestPath = new Array();
	for (int i = 0; i < this->actualPath->getSize(); i++) {
		this->bestPath->addAtTheEnd(this->actualPath->getTable()[i]);
	}
}

void TSPSimulatedAnnealing::updateActualPath()
{
	this->actualPathWeight = newPathWeight;
	delete this->actualPath;
	this->actualPath = new Array();
	for (int i = 0; i < this->newPath->getSize(); i++) {
		this->actualPath->addAtTheEnd(this->newPath->getTable()[i]);
	}
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

void TSPSimulatedAnnealing::calculateNewPathWeight()
{
	newPathWeight = 0;
	newPathWeight += matrix->distance(0, newPath->getTable()[0]);
	for (int i = 0; i < newPath->getSize() - 1; i++) {
		newPathWeight += matrix->distance(newPath->getTable()[i], newPath->getTable()[i + 1]);
	}
	newPathWeight += matrix->distance(newPath->getTable()[newPath->getSize()-1], 0);
}

double TSPSimulatedAnnealing::calculateHeuristic()
{
	double param = (double)(newPathWeight - actualPathWeight) / currentTemp;
	double result = exp(param);
	//std::cout << result << "\n";
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
	//std::cout << random << "\n";
	return random;
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
