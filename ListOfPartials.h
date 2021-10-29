#pragma once
#ifndef ListOfPartials_h
#define ListOfPartials_h

#include "PartialSolution.h"

struct element {
	element* previous = nullptr;
	PartialSolution* solution = nullptr;
	element* next = nullptr;
};

class ListOfPartials
{
public:
	ListOfPartials();
	~ListOfPartials();
	void addAtTheEnd(PartialSolution* solution);
	void removeAtTheEnd();
	void removeOnPosition(element* elem);
	void showList();

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

#endif // !ListOfPartials_h
