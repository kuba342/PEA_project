#pragma once
#ifndef Permutation_h
#define Permutation_h

#include "Array.h"

class Permutation
{
public:
	Permutation(int size);
	~Permutation();
	bool nextPermutation(int first, int last);
	int getSize();
	Array* getPermutationList();

private:
	Array* permutationList;
	int size;
};

#endif // !Permutation_h
