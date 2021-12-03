#include "TabuSearch.h"

TabuSearch::TabuSearch(AdjMatrix* graph)
{
	this->graph = graph;
	this->actualPath = new Array();
	for (int i = 1; i < this->graph->getV(); i++) {
		actualPath->addAtTheEnd(i);
	}
	this->actualPathWeight = INT_MAX;
	this->bestPath = new Array();
	this->bestPathWeight = INT_MAX;
	this->tries = 0;
	this->maxTries = 10;
	this->count = 0;
	this->Iter = 10000;
	this->tabuMatrix = new Array * [graph->getV() - 2];
	for (int i = 0; i < graph->getV() - 2; i++) {
		tabuMatrix[i] = new Array();
		for (int j = 0; j < graph->getV()-2-i; j++) {
			tabuMatrix[i]->addAtTheEnd(0);
		}
	}
	this->tabuLength = 2*graph->getV();
	this->potentialCost = INT_MAX;
	this->foundIndex1 = INT_MAX;
	this->foundIndex2 = INT_MAX;
	//Start randomizing
	srand(time(NULL));
}

TabuSearch::~TabuSearch()
{
	delete actualPath;
	delete bestPath;
	for (int i = 0; i < graph->getV() - 2; i++) {
		delete tabuMatrix[i];
	}
	delete[] tabuMatrix;
}

void TabuSearch::calculate()
{
	//Wykonujê maxTries razy g³ówn¹ pêtlê
	for (tries=1; tries <= maxTries; tries++) {
		//Wygeneruj pierwsz¹ (losow¹) trasê
		firstSolution();
		//Oblicz jej koszt
		calculateFirstSolutionWeight();
		//Jeœli pierwsza iteracja, to stwórz najlepsze rozwi¹zanie:
		if (tries == 1) {
			for (int i = 0; i < this->actualPath->getSize(); i++) {
				bestPath->addAtTheEnd(this->actualPath->getTable()[i]);
			}
			bestPathWeight = actualPathWeight;
		}
		//Iteracja wewnêtrzna - przeszukiwanie lokalne
		for (count = 1; count <= Iter; count++) {
			//Potencjalny koszt na maksimum
			potentialCost = INT_MAX;
			foundIndex1 = INT_MAX;
			foundIndex2 = INT_MAX;
			//Przeszukujê potencjalne zamiany
			for (int i = 0; i < graph->getV() - 2; i++) {
				for (int j = 0; j < tabuMatrix[i]->getSize(); j++) {
					//Jeœli zamiana nie jest Tabu
					if (notTabu(i, j)) {
						//Liczê koszt potencjalnej zamiany
						int cost = calculatePotentialWeight(i, i+j+1);
						//Jeœli mniejszy, to zapamiêtujê
						if (cost < potentialCost) {
							potentialCost = cost;
							foundIndex1 = i;
							foundIndex2 = j;
						}
					}
				}
			}

			//Aktualizujê listê tabu: wszystko -1 (oprócz 0)
			//Aktualna zamiana = tabuLength (jeœli jest ró¿na od INT_MAX)
			updateParameters();
		}
		//Aktualizacja najlepszej trasy w zale¿noœci od warunku
		if (actualPathWeight < bestPathWeight) {
			updateBestSolution();
		}
	}
}

void TabuSearch::showBestCycle()
{
	std::cout << "Najkrotsza sciezka:\n";
	std::cout << "[ 0 ";
	for (int i = 0; i < bestPath->getSize(); i++) {
		std::cout << bestPath->getTable()[i] << " ";
	}
	std::cout << "0 ]\n";
	std::cout << "Cost: " << bestPathWeight << "\n";
}

void TabuSearch::firstSolution()
{
	//Wype³niam zbiór wierzcho³ków
	for (int i = 1; i < this->graph->getV(); i++) {
		set.pushFront(i);
	}
	//Dla ka¿dego z nieu¿ytych wierzcho³ków:
	for (int i = 1; i < this->graph->getV(); i++) {
		//Losowy indeks modulo rozmiar
		int index = (std::rand() % set.getLength());
		//Dodajê na koniec wybrany element
		this->actualPath->getTable()[i - 1] = set.get(index);
		//Usuwam ze zbioru wybrany element
		set.removeAt(index);
	}
	//actualPath->showArray();
}

void TabuSearch::calculateFirstSolutionWeight()
{
	actualPathWeight = 0;
	actualPathWeight += this->graph->distance(0, actualPath->getTable()[0]);
	for (int i = 0; i < actualPath->getSize() - 1; i++) {
		actualPathWeight += this->graph->distance(actualPath->getTable()[i], actualPath->getTable()[i + 1]);
	}
	actualPathWeight += this->graph->distance(actualPath->getTable()[actualPath->getSize() - 1], 0);
}

void TabuSearch::updateBestSolution()
{
	bestPathWeight = actualPathWeight;
	for (int i = 0; i < actualPath->getSize(); i++) {
		bestPath->getTable()[i] = actualPath->getTable()[i];
	}
}

int TabuSearch::calculatePotentialWeight(int ind1, int ind2)
{
	int index1 = ind1;
	int index2 = ind2;
	int potentialWeight = actualPathWeight;
	if (ind1 > ind2) {
		int bufor = index1;
		index1 = index2;
		index2 = bufor;
	}
	//Odejmujê 4 krawêdzie bior¹ce udzia³ w zamianie
	//KrawêdŸ 1
	if (index1 == 0) {
		potentialWeight -= graph->distance(0, actualPath->getTable()[index1]);
	}
	else {
		potentialWeight -= graph->distance(actualPath->getTable()[index1 - 1], actualPath->getTable()[index1]);
	}
	//KrawêdŸ 2 - niezmienna
	potentialWeight -= graph->distance(actualPath->getTable()[index1], actualPath->getTable()[index1 + 1]);
	//KrawêdŸ 3 - niezmienna
	if (index2 - index1 != 1) {
		potentialWeight -= graph->distance(actualPath->getTable()[index2 - 1], actualPath->getTable()[index2]);
	}
	//KrawêdŸ 4
	if (index2 == actualPath->getSize()-1) {
		potentialWeight -= graph->distance(actualPath->getTable()[index2], 0);
	}
	else {
		potentialWeight -= graph->distance(actualPath->getTable()[index2], actualPath->getTable()[index2+1]);
	}

	//Zamiana
	actualPath->swap(index1, index2);
	
	//Dodajê do kosztu 4 nowe krawêdzie
	//KrawêdŸ 1
	if (index1 == 0) {
		potentialWeight += graph->distance(0, actualPath->getTable()[index1]);
	}
	else {
		potentialWeight += graph->distance(actualPath->getTable()[index1 - 1], actualPath->getTable()[index1]);
	}
	//KrawêdŸ 2 - niezmienna
	potentialWeight += graph->distance(actualPath->getTable()[index1], actualPath->getTable()[index1 + 1]);
	//KrawêdŸ 3 - niezmienna
	if (index2 - index1 != 1) {
		potentialWeight += graph->distance(actualPath->getTable()[index2 - 1], actualPath->getTable()[index2]);
	}
	//KrawêdŸ 4
	if (index2 == actualPath->getSize()-1) {
		potentialWeight += graph->distance(actualPath->getTable()[index2], 0);
	}
	else {
		potentialWeight += graph->distance(actualPath->getTable()[index2], actualPath->getTable()[index2 + 1]);
	}
	
	//Przywracam actualPath
	actualPath->swap(index1, index2);

	return potentialWeight;
}

void TabuSearch::updateParameters()
{
	//Pomniejszam elementy z tabu o 1
	for (int i = 0; i < graph->getV() - 2; i++) {
		for (int j = 0; j < tabuMatrix[i]->getSize(); j++) {
			if (tabuMatrix[i]->getTable()[j] > 0) {
				tabuMatrix[i]->getTable()[j]--;
			}
		}
	}
	//Wpisujê do znalezionych indeksów tabuLength
	if (potentialCost != INT_MAX && foundIndex1 != INT_MAX && foundIndex2 != INT_MAX) {
		tabuMatrix[foundIndex1]->getTable()[foundIndex2] = tabuLength;
		//Jeœli potentialCost < actualPathWeight, to aktualizacja actualPath
		if (potentialCost < actualPathWeight) {
			actualPath->swap(foundIndex1, foundIndex2 + foundIndex1 + 1);
			actualPathWeight = potentialCost;
		}
	}
}

bool TabuSearch::notTabu(int index1, int index2)
{
	if (tabuMatrix[index1]->getTable()[index2] == 0) {
		return true;
	}
	else {
		return false;
	}
}

Array* TabuSearch::getActualPath()
{
	return this->actualPath;
}

int TabuSearch::getActualPathWeight()
{
	return this->actualPathWeight;
}

int TabuSearch::getTries()
{
	return this->tries;
}

int TabuSearch::getMaxTries()
{
	return this->maxTries;
}

void TabuSearch::setMaxTries(int maxTries)
{
	this->maxTries = maxTries;
}

int TabuSearch::getCount()
{
	return this->count;
}

int TabuSearch::getIter()
{
	return this->Iter;
}

void TabuSearch::setIter(int Iter)
{
	this->Iter = Iter;
}
