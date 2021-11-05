#pragma once
#ifndef HeldKarp_h
#define HeldKarp_h

#include <iostream>
#include "AdjMatrix.h"
#include "Additional.h"
#include "ListOfPartials.h"
#include "PartialSolution.h"
#include "Additional.h"
#include "Combinations.h"
#include "Partial.h"

class HeldKarp
{
public:
	HeldKarp();
	HeldKarp(AdjMatrix* matrix);
	~HeldKarp();
	void calculate();
	void showShortestCycle();
	void countShortest();

private:
	Additional* lib;
	AdjMatrix* matrix;
	int weightOfShortest;
	ListOfPartials** Tab;
	PartialSolution* shortest;
	Combinations* Comb;
	BiList** goalIndexes;
	
	bool* visited;
	Partial* tsp;
	Array* tspN;
	//ListOfPartials** firstTab;
	//int firstTabLength;
	//ListOfPartials** secondTab;
	//int SecondTabLength;
	//BiList* ListOfNodes;
	
	//int currentSet;

	void algorithm2();
	void algorithm3();
	void algorithm4();
	Partial* TSP(Array* N, int begin);
	void prepare();
};

#endif // !HeldKarp_h
