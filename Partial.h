#pragma once
#ifndef Partial_h
#define Partial_h

#include "BiList.h"
#include <iostream>
#include "Array.h"

class Partial
{
public:
	Partial();
	Partial(Array* list, int dest);
	~Partial();

	//Settery
	void setDestination(int dest);
	void setList(Array* list);
	void setCost(int cost);
	//Gettery
	int getDestination();
	int getCost();
	Array* getList();

private:
	int destination;
	int cost;
	Array* list;
};

#endif // !Partial_h
