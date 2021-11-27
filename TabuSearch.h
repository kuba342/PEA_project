#pragma once
#ifndef TabuSearch_h
#define TabuSearch_h

#include "AdjMatrix.h"
#include "Array.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class TabuSearch
{
public:
	TabuSearch(AdjMatrix* graph);
	~TabuSearch();
	void calculate();

	//Settery i gettery
	Array* getActualPath();
	int getActualPathWeight();


	int getTries();
	int getMaxTries();
	void setMaxTries(int maxTries);
	int getCount();
	int getIter();
	void setIter(int Iter);

private:
	AdjMatrix* graph;
	Array* actualPath;
	int actualPathWeight;

	int tries;
	int maxTries;
	int count;
	int Iter;

	//Metody 
	void firstSolution();
	void calculateFirstSolutionWeight();	
};

#endif // !TabuSearch_h
