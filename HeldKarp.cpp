#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->sizeOfSet = 0;
	this->Tab = new ListOfPartials*[1];
	this->shortest = nullptr;
	this->table = nullptr;
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->sizeOfSet = 1;
	this->Tab = new ListOfPartials*[this->matrix->getV()+1];
	for (int i = 0; i <= this->matrix->getV(); i++) {
		this->Tab[i] = new ListOfPartials();
	}
	this->shortest = nullptr;
	this->table = new bool* [this->matrix->getV() + 1];
	for (int i = 0; i <= this->matrix->getV(); i++) {
		this->table[i] = new bool[this->matrix->getV() + 1];
	}
}

HeldKarp::~HeldKarp()
{
	for (int i = 0; i <= this->matrix->getV(); i++) {
		delete this->Tab[i];
	}
	delete this->Tab;
	for (int i = 0; i <= this->matrix->getV(); i++) {
		delete this->table[i];
	}
	delete this->table;
}

void HeldKarp::calculate() {
	prepare();
	algorithm();
	countShortest();
}

void HeldKarp::showShortestCycle() {
	if (this->shortest != nullptr) {
		std::cout << "Weight = " << this->shortest->getSumOfWeights() << "\n";
		this->shortest->getSet()->showList();
	}
	else {
		return;
	}
}

void HeldKarp::countShortest()
{
	this->shortest = new PartialSolution(this->matrix, this->matrix->getV());
	this->shortest->setDestination(0);
	element* pointer = this->Tab[this->matrix->getV()-1]->getHead();
	while(pointer != nullptr) {
		int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(), 0);
		if (weight < this->shortest->getSumOfWeights()) {
			this->shortest->deleteSet();
			for (int i = 0; i < pointer->solution->getSet()->getCount(); i++) {
				this->shortest->getSet()->addAtTheEnd(pointer->solution->getSet()->getElement(i)->key);
			}
			this->shortest->setSumOfWeights(weight);
			this->shortest->setPrevious(pointer->solution);
			this->shortest->setOneBeforeLast(pointer->solution->getDestination());
		}
		pointer = pointer->next;
	}
}

void HeldKarp::algorithm()
{
	for (int size = 2; size < this->matrix->getV(); size++, this->sizeOfSet++) {
		Combinations* comb = new Combinations(this->matrix->getV()-1, size);
		for (int i = 0; i <= this->matrix->getV(); i++) {
			for (int j = 0; j <= this->matrix->getV(); j++) {
				this->table[i][j] = false;
			}
		}
		while (comb->hasNext()) {
			
			for (int i = 0; i < size; i++) {
				
				int actualK = comb->getSolution()[i];
				//W tym miejscu w zasadzie pojawi siê nowe rozwi¹zanie
				//I sprawdzanie warunku z poprzednimi
				//ListOfPartials* list = this->Tab[size - 1];
				//std::cout << this->Tab[size - 1]->getTail() << "\n";
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				newPartial->setDestination(actualK);
				//Iterujê przez wszystkie elementy poprzedniej listy
				element* pointer = this->Tab[size - 1]->getHead();
				while (pointer != nullptr) {
					if (pointer->solution->getDestination() != actualK && (comb->searchKey(pointer->solution->getDestination()) != -1)) {
						//jeœli nie ma wierzcho³ka analizowanego w zbiorze:
						if ( (pointer->solution->getSet()->searchKey(actualK) == -1) /* && (this->table[actualK][pointer->solution->getDestination()] == false)*/  ) {
							//Liczê now¹ wagê œcie¿ki:
							//std::cout << "K = " << actualK << "\n";
							//std::cout << pointer->solution->getDestination() << "\n";
							int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(),actualK);
							//Aktualizujê nowe rozwi¹zanie:
							if (weight < newPartial->getSumOfWeights()){
								newPartial->deleteSet();
								for (int i = 0; i < pointer->solution->getSet()->getCount(); i++) {
									newPartial->getSet()->addAtTheEnd(pointer->solution->getSet()->getElement(i)->key);
								}
								newPartial->setSumOfWeights(weight);
								newPartial->setPrevious(pointer->solution);
								newPartial->setOneBeforeLast(pointer->solution->getDestination());
							}
						}
					}
					pointer = pointer->next;
				}
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualK);
					this->table[actualK][newPartial->getOneBeforeLast()] = true;
					this->Tab[size]->addAtTheEnd(newPartial);
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
	for (int i = 0; i < this->matrix->getV()-1; i++) {
		std::cout << i << ". ";
		this->Tab[1]->getElement(i)->solution->getSet()->showList();
		std::cout << "\n";
	}
}
