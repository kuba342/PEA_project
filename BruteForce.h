#pragma once
#ifndef BruteForce_h
#define BruteForce_h

#include "Array.h"
#include <iostream>
#include "AdjMatrix.h"
#include <limits.h>

class BruteForce
{
public:
	BruteForce();
	~BruteForce();
	void print();

private:
	Array* permutationList;
	Array* shortestCycle;
	int weightOfShortest;

	bool nextPermutation(int first, int last);
	//int calculateWeight();
	//void reverse(listElement* first, listElement* last);
};

#endif // !
