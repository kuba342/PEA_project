#pragma once
#ifndef PartialSolution_h
#define PartialSolution_h

#include "Array.h"
#include "AdjMatrix.h"
#include "BiList.h"
#include "BRTree.h"

class PartialSolution
{
public:
	PartialSolution();
	PartialSolution(AdjMatrix* matrix, int s);
	~PartialSolution();

	//Gettery
	int getS();
	int getDestination();
	int getSumOfWeights();
	int getOneBeforeLast();
	BiList* getSet();
	BRTree* getNodes();
	//BiList* getNodes();
	//Settery
	void setDestination(int destination);
	void setSumOfWeights(int sum);
	void setOneBeforeLast(int OneBefore);
	void setPrevious(PartialSolution* previous);
	void deleteSet();

private:
	int s;
	int destination;
	int sumOfWeight;
	int oneBeforeLast;
	BRTree* nodes;
	BiList* set;
	//BiList* nodes;
	AdjMatrix* matrix;
	PartialSolution* previous;
};

#endif // !PartialSolution_h
