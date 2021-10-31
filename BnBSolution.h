#pragma once
#ifndef BnBSolution_h
#define BnBSolution_h

#include "BiList.h"
#include <iostream>

class BnBSolution
{
public:
	BnBSolution();
	~BnBSolution();

	//Gettery i settery
	void setCost(int cost);
	int getCost();
	BiList* getCycle();

private:
	int cost;
	BiList* cycle;
};

#endif // !BnBSolution_h


