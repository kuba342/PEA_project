#pragma once
#ifndef HeldKarp_h
#define HeldKarp_h

#include <iostream>
#include "AdjMatrix.h"

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
	int weightOfShortest;
};

#endif // !HeldKarp_h
