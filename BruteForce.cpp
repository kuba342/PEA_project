#include "BruteForce.h"

BruteForce::BruteForce()
{
	this->permutationList = new Array();
	this->shortestCycle = new Array();
	this->weightOfShortest = INT_MAX;
}

BruteForce::~BruteForce()
{
}

void BruteForce::print() {
	for (int i = 1; i < 4; i++) {
		this->permutationList->addAtTheEnd(i);
	}
	std::cout << "Poczatek:\n";
	this->permutationList->showArray();
	std::cout << "\nEfekty:\n";
	int i = 2;
	while (nextPermutation(0,2)) {
		std::cout << i << ". ";
		this->permutationList->showArray();
		std::cout << "\n";
		i++;
	}
	std::cin.get();
	std::cin.get();
}

bool BruteForce::nextPermutation(int first, int last) {
	if (first == last) {
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
	}
}

