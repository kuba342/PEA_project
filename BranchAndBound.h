#pragma once
#ifndef BranchAndBound_h
#define BranchAndBound_h

#include "AdjMatrix.h"
#include "Array.h"
#include "BiList.h"
#include <iostream>
#include "BnBSolution.h"

class BranchAndBound
{
public:
	BranchAndBound(AdjMatrix* matrix);
	~BranchAndBound();
	void calculate();
	BnBSolution* getSolution();

private:
	AdjMatrix* matrix;
	Array* minWeights;
	int minValue;
	BiList* unusedNodes;
	BiList* path;
	BnBSolution* solution;

	void countMinWeights();
	void prepare();
	int heuristic(int previous, int nextNode); 
	void solveByRecursion(int heuristic);
	void updateSolution(int cost);
};

#endif // !BranchAndBound_h


