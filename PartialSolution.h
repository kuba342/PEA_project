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
	BiList* getNodes();
	//Settery
	void setDestination(int destination);
	void setSumOfWeights(int sum);
	void setOneBeforeLast(int OneBefore);

private:
	int s;
	int destination;
	int sumOfWeight;
	int oneBeforeLast;
	BiList* set;
	BiList* nodes;
	AdjMatrix* matrix;
};

#endif // !PartialSolution_h
