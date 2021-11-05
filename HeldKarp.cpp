#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->Tab = new ListOfPartials*[1];
	this->shortest = nullptr;
	this->Comb = nullptr;
	this->goalIndexes = nullptr;
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->Tab = new ListOfPartials*[this->matrix->getV()+1];
	for (int i = 0; i <= this->matrix->getV(); i++) {
		this->Tab[i] = new ListOfPartials();
	}
	this->shortest = nullptr;
	this->Comb = nullptr;
	this->goalIndexes = new BiList * [this->matrix->getV()+1];
	for (int i = 0; i <= matrix->getV(); i++) {
		this->goalIndexes[i] = new BiList();
	}
}

HeldKarp::~HeldKarp()
{
	for (int i = 0; i <= this->matrix->getV(); i++) {
		delete this->Tab[i];
	}
	delete this->Tab;
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
	algorithm5();
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
	// https://core.ac.uk/download/pdf/154419746.pdf
	//Dla ka¿dego rozmiaru podzbioru:
	for (int size = 2; size < this->matrix->getV(); size++) {
		this->Comb = new Combinations(this->matrix->getV() - 1, size);
		//Dla ka¿dego podzbioru o rozmiarze:
		while (this->Comb->hasNext()) {
			//Dla ka¿dego elementu nale¿¹cego do podzbioru:
			for (int w = 0; w < size; w++) {
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				int actualW = this->Comb->getSolution()[w];
				newPartial->setDestination(actualW);
				//Dla ka¿dego elementu ró¿nego od w:
				for (int u = 0; u < size; u++) {
					//Tu mo¿e byæ tak zrobione, poniewa¿ iterujê po tej samej tablicy
					if (u!=w) {
						int actualU = this->Comb->getSolution()[u];
						//Iterujê przez poprzedni¹ listê w poszukiwaniu S\{w}
						element* pointer = this->Tab[size - 1]->getHead();
						while (pointer != nullptr) {
							if (pointer->solution->getDestination() != actualU) {
								pointer = pointer->next;
								continue;
							}
							//Porównanie znalezionego zbioru:
							bool result = true;
							for (int j = 0; j < size; j++) {
								if (this->Comb->getSolution()[j] != actualW) {
									if (pointer->solution->getSet()->searchKey(this->Comb->getSolution()[j]) == -1) {
										result = false;
										break;
									}
								}
							}
							if (result == false) {
								pointer = pointer->next;
								continue;
							}
							//Obliczenie wagi nowego rozwi¹zania:
							int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(), actualW);
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
					}
				}
				//Dodanie nowego rozwi¹zania czêœciowego do listy:
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualW);
					this->Tab[size]->addAtTheEnd(newPartial);
				}
			}
			this->Comb->update();
		}
	}
}

void HeldKarp::algorithm4() {
	// Zmodyfikowana wersja - przez jednokrotne przeszukiwanie listy i zachowanie indeksów u
	// https://core.ac.uk/download/pdf/154419746.pdf
	//Dla ka¿dego rozmiaru podzbioru:
	for (int size = 2; size < this->matrix->getV(); size++) {
		this->Comb = new Combinations(this->matrix->getV() - 1, size);
		//Dla ka¿dego podzbioru o rozmiarze:
		while (this->Comb->hasNext()) {
			//Tablica, która przechowuje listy indeksów z wierzcho³kami docelowymi:
			//Jednokrotnie przechodzê j¹ w poszukiwaniu indeksów
			element* pointer = this->Tab[size - 1]->getHead();
			int INDEX = 0;
			while (pointer != nullptr) {
				int value = pointer->solution->getDestination();
				this->goalIndexes[value]->addAtTheEnd(INDEX);
				INDEX++;
				pointer = pointer->next;
			}
			//ZASADNICZA CZÊŒÆ ALGORYTMU:
			//Dla ka¿dego elementu nale¿¹cego do podzbioru:
			for (int w = 0; w < size; w++) {
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				int actualW = this->Comb->getSolution()[w];
				newPartial->setDestination(actualW);
				//Dla ka¿dego elementu ró¿nego od w:
				for (int u = 0; u < size; u++) {
					//Tu mo¿e byæ tak zrobione, poniewa¿ iterujê po tej samej tablicy
					if (u != w) {
						int actualU = this->Comb->getSolution()[u];
						//Teraz iterujê jedynie przez listê z konkretnymi indeksami celu:
						listElement* pointer2 = this->goalIndexes[actualU]->getHead();
						while (pointer2 != nullptr) {
							//Porównanie zbioru dla wierzcho³ka docelowego
							bool result = true;
							for (int j = 0; j < size; j++) {
								if (this->Comb->getSolution()[j] != actualW) {
									//ciekawe czy dobrze to napisa³em XD
									if (this->Tab[size-1]->getElement(pointer2->key)->solution->getSet()->searchKey(this->Comb->getSolution()[j]) == -1) {
										result = false;
										break;
									}
								}
							}
							if (result == false) {
								pointer2 = pointer2->next;
								continue;
							}
							//Obliczenie wagi nowego rozwi¹zania:
							int weight = this->Tab[size - 1]->getElement(pointer2->key)->solution->getSumOfWeights() + this->matrix->distance(this->Tab[size - 1]->getElement(pointer2->key)->solution->getDestination(), actualW);
							//Aktualizujê nowe rozwi¹zanie:
							if (weight < newPartial->getSumOfWeights()) {
								newPartial->deleteSet();
								for (int i = 0; i < this->Tab[size - 1]->getElement(pointer2->key)->solution->getSet()->getCount(); i++) {
									newPartial->getSet()->addAtTheEnd(this->Tab[size - 1]->getElement(pointer2->key)->solution->getSet()->getElement(i)->key);
								}
								newPartial->setSumOfWeights(weight);
								newPartial->setPrevious(this->Tab[size - 1]->getElement(pointer2->key)->solution);
								newPartial->setOneBeforeLast(this->Tab[size - 1]->getElement(pointer2->key)->solution->getDestination());
							}

							pointer2 = pointer2->next;
						}
					}
				}
				//Dodanie nowego rozwi¹zania czêœciowego do listy:
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualW);
					this->Tab[size]->addAtTheEnd(newPartial);
				}
			}
			//KONIEC ZASADNICZEJ CZÊŒCI ALGORYTMU
			//Czyszczenie tablicy z wierzcho³kami docelowymi:
			for (int x = 0; x <= this->matrix->getV(); x++) {
				delete this->goalIndexes[x];
				this->goalIndexes[x] = new BiList();
			}
			this->Comb->update();
		}
	}
}

void HeldKarp::algorithm5()
{
	// https://core.ac.uk/download/pdf/154419746.pdf
	//Dla ka¿dego rozmiaru podzbioru:
	for (int size = 2; size < this->matrix->getV(); size++) {
		this->Comb = new Combinations(this->matrix->getV() - 1, size);
		//Dla ka¿dego podzbioru o rozmiarze:
		while (this->Comb->hasNext()) {
			//Dla ka¿dego elementu nale¿¹cego do podzbioru:
			for (int w = 0; w < size; w++) {
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				int actualW = this->Comb->getSolution()[w];
				newPartial->setDestination(actualW);
				//Dla ka¿dego elementu ró¿nego od w:
				for (int u = 0; u < size; u++) {
					//Tu mo¿e byæ tak zrobione, poniewa¿ iterujê po tej samej tablicy
					if (u != w) {
						int actualU = this->Comb->getSolution()[u];
						//Iterujê przez poprzedni¹ listê w poszukiwaniu S\{w}
						element* pointer = this->Tab[size - 1]->getHead();
						while (pointer != nullptr) {
							if (pointer->solution->getDestination() != actualU) {
								pointer = pointer->next;
								continue;
							}
							//Porównanie znalezionego zbioru:
							bool result = true;
							for (int j = 0; j < size; j++) {
								if (this->Comb->getSolution()[j] != actualW) {
									if (pointer->solution->getNodes()->contains(this->Comb->getSolution()[j]) == false) {
										result = false;
										break;
									}
								}
							}
							if (result == false) {
								pointer = pointer->next;
								continue;
							}
							//Obliczenie wagi nowego rozwi¹zania:
							int weight = pointer->solution->getSumOfWeights() + this->matrix->distance(pointer->solution->getDestination(), actualW);
							//Aktualizujê nowe rozwi¹zanie:
							if (weight < newPartial->getSumOfWeights()) {
								newPartial->deleteSet();
								for (int i = 0; i < pointer->solution->getSet()->getCount(); i++) {
									newPartial->getSet()->addAtTheEnd(pointer->solution->getSet()->getElement(i)->key);
									newPartial->getNodes()->addElement(pointer->solution->getSet()->getElement(i)->key);
								}
								newPartial->setSumOfWeights(weight);
								newPartial->setPrevious(pointer->solution);
								newPartial->setOneBeforeLast(pointer->solution->getDestination());
							}

							pointer = pointer->next;
						}
					}
				}
				//Dodanie nowego rozwi¹zania czêœciowego do listy:
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualW);
					newPartial->getNodes()->addElement(actualW);
					this->Tab[size]->addAtTheEnd(newPartial);
				}
			}
			this->Comb->update();
		}
	}
}

void HeldKarp::algorithm6()
{
	// Zmodyfikowana wersja - przez jednokrotne przeszukiwanie listy i zachowanie indeksów u
	// https://core.ac.uk/download/pdf/154419746.pdf
	//Dla ka¿dego rozmiaru podzbioru:
	for (int size = 2; size < this->matrix->getV(); size++) {
		this->Comb = new Combinations(this->matrix->getV() - 1, size);
		//Dla ka¿dego podzbioru o rozmiarze:
		while (this->Comb->hasNext()) {
			//Tablica, która przechowuje listy indeksów z wierzcho³kami docelowymi:
			//Jednokrotnie przechodzê j¹ w poszukiwaniu indeksów
			element* pointer = this->Tab[size - 1]->getHead();
			int INDEX = 0;
			while (pointer != nullptr) {
				int value = pointer->solution->getDestination();
				this->goalIndexes[value]->addAtTheEnd(INDEX);
				INDEX++;
				pointer = pointer->next;
			}
			//ZASADNICZA CZÊŒÆ ALGORYTMU:
			//Dla ka¿dego elementu nale¿¹cego do podzbioru:
			for (int w = 0; w < size; w++) {
				PartialSolution* newPartial = new PartialSolution(this->matrix, size);
				int actualW = this->Comb->getSolution()[w];
				newPartial->setDestination(actualW);
				//Dla ka¿dego elementu ró¿nego od w:
				for (int u = 0; u < size; u++) {
					//Tu mo¿e byæ tak zrobione, poniewa¿ iterujê po tej samej tablicy
					if (u != w) {
						int actualU = this->Comb->getSolution()[u];
						//Teraz iterujê jedynie przez listê z konkretnymi indeksami celu:
						listElement* pointer2 = this->goalIndexes[actualU]->getHead();
						while (pointer2 != nullptr) {
							//Porównanie zbioru dla wierzcho³ka docelowego
							bool result = true;
							for (int j = 0; j < size; j++) {
								if (this->Comb->getSolution()[j] != actualW) {
									//ciekawe czy dobrze to napisa³em XD
									if (this->Tab[size - 1]->getElement(pointer2->key)->solution->getNodes()->contains(this->Comb->getSolution()[j]) == false) {
										result = false;
										break;
									}
								}
							}
							if (result == false) {
								pointer2 = pointer2->next;
								continue;
							}
							//Obliczenie wagi nowego rozwi¹zania:
							int weight = this->Tab[size - 1]->getElement(pointer2->key)->solution->getSumOfWeights() + this->matrix->distance(this->Tab[size - 1]->getElement(pointer2->key)->solution->getDestination(), actualW);
							//Aktualizujê nowe rozwi¹zanie:
							if (weight < newPartial->getSumOfWeights()) {
								newPartial->deleteSet();
								for (int i = 0; i < this->Tab[size - 1]->getElement(pointer2->key)->solution->getSet()->getCount(); i++) {
									newPartial->getSet()->addAtTheEnd(this->Tab[size - 1]->getElement(pointer2->key)->solution->getSet()->getElement(i)->key);
									newPartial->getNodes()->addElement(this->Tab[size - 1]->getElement(pointer2->key)->solution->getSet()->getElement(i)->key);
								}
								newPartial->setSumOfWeights(weight);
								newPartial->setPrevious(this->Tab[size - 1]->getElement(pointer2->key)->solution);
								newPartial->setOneBeforeLast(this->Tab[size - 1]->getElement(pointer2->key)->solution->getDestination());
							}

							pointer2 = pointer2->next;
						}
					}
				}
				//Dodanie nowego rozwi¹zania czêœciowego do listy:
				if (newPartial->getOneBeforeLast() != INT_MAX) {
					newPartial->getSet()->addAtTheEnd(actualW);
					newPartial->getNodes()->addElement(actualW);
					this->Tab[size]->addAtTheEnd(newPartial);
				}
			}
			//KONIEC ZASADNICZEJ CZÊŒCI ALGORYTMU
			//Czyszczenie tablicy z wierzcho³kami docelowymi:
			for (int x = 0; x <= this->matrix->getV(); x++) {
				delete this->goalIndexes[x];
				this->goalIndexes[x] = new BiList();
			}
			this->Comb->update();
		}
	}
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
		this->Tab[1]->getElement(i - 1)->solution->getNodes()->addElement(i);
	}
}

