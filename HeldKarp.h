#pragma once
#ifndef HeldKarp_h
#define HeldKarp_h

#include <iostream>
#include "AdjMatrix.h"
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
	AdjMatrix* matrix;
	Additional* lib;
	int weightOfShortest;
};

#endif // !HeldKarp_h
