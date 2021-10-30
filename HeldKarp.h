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
	int sizeOfSet;
	ListOfPartials** Tab;
	PartialSolution* shortest;
	bool** table;

	//ListOfPartials** firstTab;
	//int firstTabLength;
	//ListOfPartials** secondTab;
	//int SecondTabLength;
	//BiList* ListOfNodes;
	
	//int currentSet;

	void algorithm();
	void prepare();
	void update();
	void iteration();
	void iterationForSet();
	void deletTable();
};

#endif // !HeldKarp_h
