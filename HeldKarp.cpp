#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	//this->firstTab = nullptr;
	//this->secondTab = nullptr;
	this->sizeOfSet = 0;
	//this->currentSet = 0;
	//this->ListOfNodes = nullptr;
	//this->firstTabLength = 0;
	//this->SecondTabLength = 0;
	this->Tab = new ListOfPartials*[1];
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	//this->firstTab = nullptr;
	//this->secondTab = nullptr;
	this->sizeOfSet = 1;
	//this->currentSet = 0;
	//this->ListOfNodes = nullptr;
	//this->firstTabLength = 0;
	//this->SecondTabLength = 0;
	this->Tab = new ListOfPartials*[this->matrix->getV()+1];
	for (int i = 0; i <= this->matrix->getV(); i++) {
		this->Tab[i] = new ListOfPartials();
	}
}

HeldKarp::~HeldKarp()
{
}

void HeldKarp::calculate() {
	prepare();
	algorithm();
}

void HeldKarp::showShortestCycle() {

}

void HeldKarp::algorithm()
{
	prepare();
	for (sizeOfSet = 2; sizeOfSet < this->matrix->getV(); sizeOfSet++) {
		Combinations* comb = new Combinations(this->matrix->getV()-1, this->sizeOfSet);
		while (comb->hasNext()) {
			for (int i = 0; i < sizeOfSet; i++) {
				int actualK = comb->getSolution()[i];
				//W tym miejscu w zasadzie pojawi siê nowe rozwi¹zanie
				//I sprawdzanie warunku z poprzednimi
				ListOfPartials* list = this->Tab[sizeOfSet - 1];
				PartialSolution* newPartial = new PartialSolution(this->matrix, sizeOfSet);
				//Iterujê przez wszystkie elementy poprzedniej listy
				for (element* pointer = list->getHead(); pointer != list->getTail()->next; pointer = pointer->next) {
					if (pointer->solution->getDestination() != actualK) {
						//jeœli nie ma wierzcho³ka analizowanego w zbiorze:
						if (pointer->solution->getSet()->searchKey(actualK) == -1) {
							//Liczê now¹ wagê œcie¿ki:
							std::cout << "K = " << actualK << "\n";
							std::cout << pointer->solution->getDestination() << "\n";
							int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(),actualK);
							//Aktualizujê nowe rozwi¹zanie:
							if (weight < newPartial->getSumOfWeights()) {
								newPartial->setSumOfWeights(weight);
								newPartial->setDestination(actualK);
								newPartial->setPrevious(pointer->solution);
							}
						}
					}
				}
			}
			comb->update();
		}
	}
}

//Powinno byæ gotowe
void HeldKarp::prepare() {
	for (int i = 1; i < this->matrix->getV(); i++) {
		int input = this->matrix->distance(0, i);
		PartialSolution* sol = new PartialSolution(this->matrix, this->sizeOfSet);
		this->Tab[sizeOfSet]->addAtTheEnd(sol);
		this->Tab[sizeOfSet]->getElement(i - 1)->solution->setSumOfWeights(input);
		this->Tab[sizeOfSet]->getElement(i - 1)->solution->setDestination(i);
		this->Tab[sizeOfSet]->getElement(i - 1)->solution->setOneBeforeLast(0);
		this->Tab[sizeOfSet]->getElement(i - 1)->solution->getSet()->addAtTheEnd(i);
	}
	this->sizeOfSet = this->sizeOfSet + 1;
}













/*
void HeldKarp::update() {
	this->firstTab = this->secondTab;
	this->firstTabLength = this->SecondTabLength;
	this->SecondTabLength = (int)this->lib->Newton(this->ListOfNodes->getCount(),this->sizeOfSet);
	this->secondTab = new ListOfPartials * [SecondTabLength];
	for (int i = 0; i < SecondTabLength; i++) {
		//Nowo tworzona lista powinna mieæ rozmiar:
		//this->ListOfNodes->getCount() - this->sizeOfSet - 1
		secondTab[i] = new ListOfPartials();
	}
}*/

/*
void HeldKarp::iteration() {
	update();

	for (currentSet = 0; currentSet < this->firstTabLength; currentSet++) {
		iterationForSet();
	}
}*/

/*void HeldKarp::iterationForSet() {
	for (int i = 0; i < firstTab[currentSet]->getSize(); i++) {

		//this->firstTab[currentSet]->getElement(i)->solution.getSet()->addAtTheEnd()
		PartialSolution &list = this->firstTab[currentSet]->getElement(i)->solution;
		//this->firstTab[currentSet]->getElement(i)->solution.getSet()->addAtTheEnd();
		list.getSet()->addAtTheEnd(list.getDestination());
		list.getNodes()->addAtTheEnd(list.getDestination());

		BiList* unusedNodes = new BiList();
		const int n = this->matrix->getV() - 1;
		const int k = list.getNodes()->getCount();

		for (int i = 1; i < this->matrix->getV(); i++) {
			if (list.getSet()->searchKey(i) != -1) {

			}
			else {
				unusedNodes->addAtTheEnd(i);
			}
		}

		for (int j = 0; j < unusedNodes->getCount(); j++) {

		}
	}
}*/