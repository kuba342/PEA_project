#pragma once
#ifndef Combinations_h
#define Combinations_h

#include "Additional.h"
#include <iostream>

class Combinations
{
public:
	Combinations();
	Combinations(int n, int k);
	~Combinations();
	bool hasNext();
	void print();
	void update();
	int searchKey(int key);
	//Gettery
	int* getTab();
	int* getSolution();

private:
	Additional* lib;
	int* Tab;
	int* solution;
	int n;
	int k;
	int repetitions;
	int index;
};

#endif // !Combinations_h
