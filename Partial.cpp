#include "Partial.h"

Partial::Partial() {
	this->cost = INT_MAX;
	this->list = new Array();
	this->destination = 0;
}

Partial::Partial(Array* list,int dest) {
	this->cost = INT_MAX;
	this->list = list;
	this->destination = dest;
}

Partial::~Partial() {
	delete this->list;
}

void Partial::setDestination(int dest)
{
	this->destination = dest;
}

void Partial::setList(Array* list)
{
	this->list = list;
}

void Partial::setCost(int cost)
{
	this->cost = cost;
}

int Partial::getDestination() {
	return this->destination;
}

int Partial::getCost()
{
	return this->cost;
}

Array* Partial::getList()
{
	return this->list;
}

