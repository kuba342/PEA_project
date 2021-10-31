#pragma once
#ifndef BranchAndBound_h
#define BranchAndBound_h

#include "AdjMatrix.h"
#include "Array.h"
#include "BiList.h"
#include <iostream>

class BranchAndBound
{
public:
	BranchAndBound(AdjMatrix* matrix);
	~BranchAndBound();
	void calculate();

private:
	AdjMatrix* matrix;
	Array* minWeights;
	int minValue;
	BiList* unusedNodes;
	BiList* path;

	void countMinWeights();
	void prepare();
	int heuristic(int previous, int nextNode);
};

#endif // !BranchAndBound_h


