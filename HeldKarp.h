#pragma once
#ifndef HeldKarp_h
#define HeldKarp_h

#include <iostream>
#include "AdjMatrix.h"
#include "Additional.h"
#include "ListOfPartials.h"
#include "PartialSolution.h"

class HeldKarp
{
public:
	HeldKarp();
	HeldKarp(AdjMatrix* matrix);
	~HeldKarp();
	void calculate();
	void showShortestCycle();

private:
	AdjMatrix* matrix;
	Additional* lib;
	int weightOfShortest;
	ListOfPartials* firstList;
	ListOfPartials* secondList;
	int sizeOfSet;

	void algorithm();
};

#endif // !HeldKarp_h
