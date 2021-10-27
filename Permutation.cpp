#include "Permutation.h"

Permutation::Permutation(int size)
{
	this->permutationList = new Array();
	this->size = size;
	for (int i = 1; i < size; i++) {
		this->permutationList->addAtTheEnd(i);
	}
}

Permutation::~Permutation()
{
}

bool Permutation::nextPermutation(int first, int last) {
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

int Permutation::getSize() {
	return this->size;
}

Array* Permutation::getPermutationList() {
	return this->permutationList;
}