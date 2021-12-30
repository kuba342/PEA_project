#include "Individual.h"

Individual::Individual(int size)
{
	this->size = size;
	this->cost = INT_MAX;
	this->path = new BiList();
	//Wype³niam na pocz¹tku zerami, poniewa¿ losowanie bêdzie 
	//bezpoœrednio z poziomu algorytmu
	for (int i = 0; i < size; i++) {
		this->path->addAtTheEnd(0);
	}
}

Individual::~Individual()
{
	delete this->path;
}

int Individual::getCost()
{
	return this->cost;
}

int Individual::getSize()
{
	return this->size;
}

BiList* Individual::getPath()
{
	return this->path;
}

void Individual::setCost(int cost)
{
	this->cost = cost;
}
