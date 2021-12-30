#pragma once
#ifndef ListOfIndividuals_h
#define ListOfIndividuals_h

#include "Individual.h"

struct elemIn {
	elemIn* previous = nullptr;
	Individual* individual = nullptr;
	elemIn* next = nullptr;
};

class ListOfIndividuals
{
public:
	ListOfIndividuals();
	~ListOfIndividuals();

	void addAtTheEnd(Individual* individual);
	void removeOnPosition(elemIn* elem);
	void removeOnPosition(int indeks);
	void removeAtTheEnd();

	//Gettery
	int getSize();
	elemIn* getElement(int indeks);
	elemIn* getHead();
	elemIn* getTail();

private:
	int size;
	elemIn* head;
	elemIn* tail;
};

#endif // !ListOfIndividuals_h
