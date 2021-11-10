#include "BruteForce.h"

BruteForce::BruteForce()
{
	//this->permutationList = new Array();
	this->perm = new Permutation(0);
	this->shortestCycle = new Array();
	this->weightOfShortest = INT_MAX;
	this->matrix = nullptr;
}

BruteForce::BruteForce(AdjMatrix* matrix) {
	this->matrix = matrix;
	//this->permutationList = new Array();
	//for (int i = 1; i < this->matrix->getV(); i++) {
		//this->permutationList->addAtTheEnd(i);
	//}
	this->perm = new Permutation(this->matrix->getV());
	//this->shortestCycle = new Array();
	this->shortestCycle = nullptr;
	this->weightOfShortest = INT_MAX;
}

BruteForce::~BruteForce()
{
}

void BruteForce::Cycle() {
	this->shortestCycle = new Array();
	this->shortestCycle->addAtTheEnd(0);
	//for (int i = 0; i < this->permutationList->getSize(); i++) {
		//this->shortestCycle->addAtTheEnd(this->permutationList->getTable()[i]);
	//}
	for (int i = 0; i < this->perm->getPermutationList()->getSize(); i++) {
		this->shortestCycle->addAtTheEnd(this->perm->getPermutationList()->getTable()[i]);
	}
	this->shortestCycle->addAtTheEnd(0);
}

void BruteForce::calculate() {
	int weight = 0;
	do {
		//obliczenie wagi dla aktualnego cyklu
		weight = calculateWeight();
		//JEœli waga mniejsza, to zapamiêtujê wagê i przepisujê cykl
		if (weight < this->weightOfShortest) {
			this->weightOfShortest = weight;
			Cycle();
		}
		//Dopóki istnieje nastêpna permutacja
	} while (this->perm->nextPermutation(0,this->perm->getPermutationList()->getSize()-1));
}

int BruteForce::calculateWeight() {
	int weight = 0;
	//weight += this->matrix->getMatrix()[0][this->permutationList->getTable()[0]];
	weight += this->matrix->getMatrix()[0][this->perm->getPermutationList()->getTable()[0]];
	/*for (int i = 0; i < this->permutationList->getSize() - 1; i++) {
		weight += this->matrix->getMatrix()[  this->permutationList->getTable()[i]  ][  this->permutationList->getTable()[i+1]  ];
	}*/
	for (int i = 0; i < this->perm->getPermutationList()->getSize() - 1; i++) {
		weight += this->matrix->getMatrix()[this->perm->getPermutationList()->getTable()[i]][this->perm->getPermutationList()->getTable()[i + 1]];
	}
	//weight += this->matrix->getMatrix()[this->permutationList->getTable()[this->permutationList->getSize()-1]][0];
	weight += this->matrix->getMatrix()[  this->perm->getPermutationList()->getTable()[this->perm->getPermutationList()->getSize()-1]  ][0];
	return weight;
}

void BruteForce::showShortestCycle() {
	std::cout << "Cycle:  [";
	for (int i = 0; i < this->shortestCycle->getSize(); i++) {
		printf(" %d ", this->shortestCycle->getTable()[i]);
	}
	std::cout << "]\n";
	std::cout << "Waga: " << this->weightOfShortest << "\n";
}

void BruteForce::print() {
	/*for (int i = 1; i < 5; i++) {
		this->permutationList->addAtTheEnd(i);
	}
	std::cout << "Poczatek:\n";
	this->permutationList->showArray();
	std::cout << "\nEfekty:\n";
	int i = 2;
	while (nextPermutation(0,3)) {
		std::cout << i << ". ";
		this->permutationList->showArray();
		std::cout << "\n";
		i++;
	}
	std::cin.get();
	std::cin.get();*/
}

bool BruteForce::nextPermutation(int first, int last) {
	/*if (first == last) {
		return false;
	}
	int i = last;
	if (first == last) {
		return false;
	}

	while (true) {
		int i1, i2;

		i1 = i;
		if (this->permutationList->getTable()[--i] < this->permutationList->getTable()[i1]) {
			i2 = last;
			//while (!(this->permutationList->getTable()[i] < this->permutationList->getTable()[--i2]));
			do {
				if (!(this->permutationList->getTable()[i] < this->permutationList->getTable()[i2])) {
					--i2;
				}
			} while (!(this->permutationList->getTable()[i] < this->permutationList->getTable()[i2]));
			this->permutationList->swap(i, i2);
			this->permutationList->reverse(i1, last);
			return true;
		}
		if (i == first) {
			this->permutationList->reverse(first, last);
			return false;
		}
	}*/
	return true;
}

