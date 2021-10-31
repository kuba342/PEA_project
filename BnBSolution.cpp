#include "BnBSolution.h"

BnBSolution::BnBSolution()
{
	this->cost = INT_MAX;
	this->cycle = new BiList();
}

BnBSolution::~BnBSolution()
{
}

void BnBSolution::setCost(int cost)
{
	this->cost = cost;
}

int BnBSolution::getCost()
{
	return this->cost;
}

BiList* BnBSolution::getCycle()
{
	return this->cycle;
}
