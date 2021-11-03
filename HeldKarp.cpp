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
	this->Comb = nullptr;
	this->visited = nullptr;
	this->tsp = nullptr;
	this->tspN = nullptr;
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
	this->Comb = nullptr;
	this->table = new bool* [this->matrix->getV() + 1];
	for (int i = 0; i <= this->matrix->getV(); i++) {
		this->table[i] = new bool[this->matrix->getV() + 1];
	}
	this->visited = new bool[matrix->getV()];
	this->tsp = nullptr;
	this->tspN = new Array();
	for (int i = 0; i < this->matrix->getV(); i++) {
		this->tspN->addAtTheEnd(i);
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
	/*for (int i = 0; i < matrix->getV(); i++) {
		visited[i] = false;
	}
	this->tsp = new Partial();
	this->tsp = TSP(this->tspN, 0);
	std::cout << "Dest = " << tsp->getDestination() << "\n";
	tsp->getList()->showArray();
	std::cout << "Cost = " << tsp->getCost();
	std::cin.get();
	std::cin.get();*/
	prepare();
	algorithm4();
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
		delete comb;
	}
}

void HeldKarp::algorithm2() {
	//Generuj kombinacje o rozmiarze
	for (int size = 2; size < this->matrix->getV(); size++) {
		this->Comb = new Combinations(this->matrix->getV() - 1, size);
		//Dla ka¿dego podzbioru kombinacji po k
		while (this->Comb->hasNext()) {
			//Iterujê po ka¿dym elemencie podzbioru
			for (int i = 0; i < size; i++) {
				//wyznaczam ten element
				int actualK = this->Comb->getSolution()[i];
				//Nowe rozwi¹zanie:
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				newPartial->setDestination(actualK);
				//Iterujê przez wszystkie elementy poprzedniej listy
				element* pointer = this->Tab[size - 1]->getHead();
				while (pointer != nullptr) {
					if (pointer->solution->getDestination() == actualK || this->Comb->searchKey(pointer->solution->getDestination()) == -1) {
						pointer = pointer->next;
						continue;
					}
					//Muszê zrobiæ porównywanie zbiorów!!!!
					bool result = true;
					for (int j = 0; j < size; j++) {
						if (this->Comb->getSolution()[j] != actualK) {
							if (pointer->solution->getSet()->searchKey(this->Comb->getSolution()[j]) == -1) {
								result = false;
							}
						}
					}
					if (result == false) {
						pointer = pointer->next;
						continue;
					}
					int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(), actualK);
					//Aktualizujê nowe rozwi¹zanie:
					if (weight < newPartial->getSumOfWeights()) {
						newPartial->deleteSet();
						for (int i = 0; i < pointer->solution->getSet()->getCount(); i++) {
							newPartial->getSet()->addAtTheEnd(pointer->solution->getSet()->getElement(i)->key);
						}
						newPartial->setSumOfWeights(weight);
						newPartial->setPrevious(pointer->solution);
						newPartial->setOneBeforeLast(pointer->solution->getDestination());
					}
					pointer = pointer->next;
				}
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualK);
					this->Tab[size]->addAtTheEnd(newPartial);
				}
			}
			this->Comb->update();
		}
	}
}


void HeldKarp::algorithm3() {
	for (int size = 2; size < this->matrix->getV()-1; size++) {
		//Iterujê przez wszystkie elementy poprzedniego zbioru:
		element* pointer = this->Tab[size-1]->getHead();
		while (pointer != nullptr) {
			for (int i = 0; i < pointer->solution->getSet()->getCount(); i++) {

			}
			pointer = pointer->next;
		}
	}
}

void HeldKarp::algorithm4() {
	//Generuj kombinacje o rozmiarze
	for (int size = 2; size < this->matrix->getV(); size++) {
		this->Comb = new Combinations(this->matrix->getV() - 1, size);
		bool* visited = new bool[this->matrix->getV()];
		for (int w = 0; w < this->matrix->getV(); w++) {
			visited[w] = false;
		}
		//Dla ka¿dego podzbioru kombinacji po k
		while (this->Comb->hasNext()) {
			//Iterujê po ka¿dym elemencie podzbioru
			for (int i = 0; i < size; i++) {
				//wyznaczam ten element
				int actualK = this->Comb->getSolution()[i];
				//visited[actualK] = true;
				//Nowe rozwi¹zanie:
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				newPartial->setDestination(actualK);
				//Iterujê przez wszystkie elementy poprzedniej listy
				element* pointer = this->Tab[size - 1]->getHead();
				while (pointer != nullptr) {
					if (pointer->solution->getDestination() == actualK /* || this->Comb->searchKey(pointer->solution->getDestination()) == -1*/) {
						pointer = pointer->next;
						continue;
					}
					//Muszê zrobiæ porównywanie zbiorów!!!!
					if (visited[pointer->solution->getDestination()] == true) {
						pointer = pointer->next;
						continue;
					}
					bool result = true;
					for (int j = 0; j < size; j++) {
						if (this->Comb->getSolution()[j] != actualK) {
							if (pointer->solution->getSet()->searchKey(this->Comb->getSolution()[j]) == -1) {
								result = false;
							}
						}
					}
					if (result == false) {
						pointer = pointer->next;
						continue;
					}
					int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(), actualK);
					//Aktualizujê nowe rozwi¹zanie:
					if (weight < newPartial->getSumOfWeights()) {
						newPartial->deleteSet();
						for (int i = 0; i < pointer->solution->getSet()->getCount(); i++) {
							newPartial->getSet()->addAtTheEnd(pointer->solution->getSet()->getElement(i)->key);
						}
						newPartial->setSumOfWeights(weight);
						newPartial->setPrevious(pointer->solution);
						newPartial->setOneBeforeLast(pointer->solution->getDestination());
					}
					pointer = pointer->next;
				}
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualK);
					this->Tab[size]->addAtTheEnd(newPartial);
					visited[actualK] = true;
				}
			}
			this->Comb->update();
		}
	}
}

/*Partial HeldKarp::TSP(Array N, int begin) {
	Partial cost;
	this->visited[begin] = true;
	if (N.getSize() == 2) {
		for (int k = 0; k < N.getSize(); k++) {
			if (k != begin) {
				cost.setList(N);
				cost.setDestination(k);
				cost.setCost(this->matrix->distance(begin, k));
				return cost;
			}
		}
	}
	else {
		for (int j = 0; j < N.getSize(); j++) {
			for (int i = 0; i < N.getSize(); i++) {
				if (j != i && j != begin) {
					Array list;
					//Przepisujê listê bez i
					for (int n = 0; n < N.getSize(); n++) {
						if (n != i) {
							list.addAtTheEnd(N.getTable()[n]);
						}
					}
					//Wyznaczam rekurencyjnie TSP
					Partial prev;
					prev = TSP(list, j);
					int weight = prev.getCost() + this->matrix->distance(j, i);
					if (weight < cost.getCost()) {
						//Aktualizujê rozwi¹zanie
						cost.setDestination(j);
						cost.setList(list);
						cost.setCost(weight);
					}
					this->visited[j] = true;
				}
			}
		}
	}
	return cost;
}*/

Partial* HeldKarp::TSP(Array* N, int begin) {
	Partial* cost = new Partial();
	this->visited[begin] = true;
	if (N->getSize() == 2) {
		for (int k = 0; k < N->getSize(); k++) {
			if (N->getTable()[k] != begin) {
				cost->setList(N);
				cost->setDestination(N->getTable()[k]);
				cost->setCost(this->matrix->distance(begin, N->getTable()[k]));
				return cost;
			}
		}
	}
	else {
		for (int j = 0; j < N->getSize(); j++) {
			for (int i = 0; i < N->getSize(); i++) {
				if (N->getTable()[j] != N->getTable()[i] && N->getTable()[j] != begin) {
					Array* list = new Array();
					//Przepisujê listê bez i
					for (int n = 0; n < N->getSize(); n++) {
						if (N->getTable()[n] != N->getTable()[i]) {
							list->addAtTheEnd(N->getTable()[n]);
						}
					}
					//Wyznaczam rekurencyjnie TSP
					Partial* prev = TSP(list, N->getTable()[j]);
					int weight = prev->getCost() + this->matrix->distance(N->getTable()[j], N->getTable()[i]);
					if (weight < cost->getCost()) {
						//Aktualizujê rozwi¹zanie
						cost->setDestination(N->getTable()[j]);
						cost->setList(list);
						cost->setCost(weight);
					}
					this->visited[N->getTable()[j]] = true;
				}
			}
		}
	}
	return cost;
}


//Powinno byæ gotowe
void HeldKarp::prepare() {
	for (int i = 1; i < this->matrix->getV(); i++) {
		int input = this->matrix->distance(0, i);
		PartialSolution* sol = new PartialSolution(this->matrix, 1);
		this->Tab[1]->addAtTheEnd(sol);
		this->Tab[1]->getElement(i - 1)->solution->setSumOfWeights(input);
		this->Tab[1]->getElement(i - 1)->solution->setDestination(i);
		this->Tab[1]->getElement(i - 1)->solution->setOneBeforeLast(0);
		this->Tab[1]->getElement(i - 1)->solution->getSet()->addAtTheEnd(i);
	}
}

