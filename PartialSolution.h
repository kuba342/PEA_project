#pragma once
#ifndef PartialSolution_h
#define PartialSolution_h

#include "Array.h"
#include "AdjMatrix.h"
#include "BiList.h"

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

private:
	int s;
	int destination;
	int sumOfWeight;
	int oneBeforeLast;
	BiList* set;
	AdjMatrix* matrix;
};

#endif // !PartialSolution_h
