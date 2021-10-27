#pragma once
#ifndef BruteForce_h
#define BruteForce_h

#include "Array.h"
#include <iostream>
#include "AdjMatrix.h"
#include <limits.h>
#include "Permutation.h"

class BruteForce
{
public:
	BruteForce();
	BruteForce(AdjMatrix* matrix);
	~BruteForce();
	void print();
	
	void showShortestCycle();
	void calculate();

private:
	//Array* permutationList;
	Array* shortestCycle;
	int weightOfShortest;
	AdjMatrix* matrix;
	Permutation* perm;

	bool nextPermutation(int first, int last);
	int calculateWeight();
	void Cycle();
};

#endif // !
