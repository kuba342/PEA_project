#include "TabuSearch.h"

TabuSearch::TabuSearch(AdjMatrix* graph)
{
	this->graph = graph;
	this->actualPath = new Array();
	this->actualPathWeight = INT_MAX;
	this->tries = 0;
	this->maxTries = 5;
	this->count = 0;
	this->Iter = 5;
}

TabuSearch::~TabuSearch()
{
}

void TabuSearch::calculate()
{
	//Wykonuj� maxTries razy g��wn� p�tl�
	for (tries=1; tries <= maxTries; tries++) {
		//Wygeneruj pierwsz� (losow�) tras�
		firstSolution();
		//Oblicz jej koszt
		calculateFirstSolutionWeight();
		//Iteracja wewn�trzna
		for (count = 1; count <= Iter; count++) {

		}
		//Aktualizacja najlepszej trasy w zale�no�ci od warunku

	}
}

void TabuSearch::firstSolution()
{
	//Wype�niam zbi�r wierzcho�k�w
	Array* set = new Array();
	for (int i = 1; i < this->graph->getV(); i++) {
		set->addAtTheEnd(i);
	}
	//Dla ka�dego z nieu�ytych wierzcho�k�w:
	for (int i = 1; i < this->graph->getV(); i++) {
		//Losowy indeks modulo rozmiar
		int index = (std::rand() % set->getSize());
		//Dodaj� na koniec wybrany element
		this->actualPath->addAtTheEnd(set->getTable()[index]);
		//this->newPath->addAtTheEnd(set->getTable()[index]);
		//Usuwam ze zbioru wybrany element
		set->removeOnPosition(index);
	}
	delete set;
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
