#pragma once
#ifndef HeldKarp_h
#define HeldKarp_h

#include <iostream>
#include "AdjMatrix.h"
#include "Additional.h"
#include "ListOfPartials.h"
#include "PartialSolution.h"
#include "Additional.h"

class HeldKarp
{
public:
	HeldKarp();
	HeldKarp(AdjMatrix* matrix);
	~HeldKarp();
	void calculate();
	void showShortestCycle();

private:
	Additional* lib;
	AdjMatrix* matrix;
	int weightOfShortest;
	ListOfPartials** firstTab;
	int firstTabLength;
	ListOfPartials** secondTab;
	int SecondTabLength;
	BiList* ListOfNodes;
	int sizeOfSet;
	int currentSet;

	void algorithm();
	void prepare();
	void update();
	void iteration();
	void iterationForSet();
};

#endif // !HeldKarp_h
