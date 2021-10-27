#pragma once
#ifndef ArrayOfPartials_h
#define ArrayOfPartials_h

#include "PartialSolution.h"

struct element {
	element* previous = nullptr;
	PartialSolution solution;
	element* next = nullptr;
};

class ListOfPartials
{
public:
	ListOfPartials();
	~ListOfPartials();
	void addAtTheEnd(PartialSolution solution);
	void removeAtTheEnd();
	void removeOnPosition(element* elem);

	//Gettery
	int getSize();
	element* getElement(int indeks);
	element* getHead();
	element* getTail();

private:
	int size;
	element* head;
	element* tail;
};

#endif // !ArrayOfPartials_h
