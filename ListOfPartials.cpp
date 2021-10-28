#include "ListOfPartials.h"

ListOfPartials::ListOfPartials()
{
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

ListOfPartials::~ListOfPartials()
{
	while (this->size) {
		removeAtTheEnd();
	}
}

void ListOfPartials::addAtTheEnd(PartialSolution solution)
{
	element* pointer;
	pointer = new element;
	pointer->solution = solution;
	pointer->next = nullptr;
	pointer->previous = this->tail;
	this->tail = pointer;
	this->size++;
	if (pointer->previous) {
		pointer->previous->next = pointer;
	}
	else {
		this->head = pointer;
	}
}

void ListOfPartials::removeAtTheEnd()
{
	if (this->size) {
		removeOnPosition(this->tail);
	}
}

void ListOfPartials::removeOnPosition(element* elem)
{
	this->size--;
	if (elem->previous) {
		elem->previous->next = elem->next;
	}
	else {
		this->head = elem->next;     //W przeciwnym razie do czo³a przypisujê nastêpnik
	}

	if (elem->next) {
		elem->next->previous = elem->previous;
	}
	else {
		this->tail = elem->previous;
	}

	delete elem;
}

int ListOfPartials::getSize()
{
	return this->size;
}

element* ListOfPartials::getElement(int indeks)
{
	element* pointer = this->head;
	if (indeks <= this->size) {
		if (indeks == 0) {
			return this->head;
		}
		for (int i = 0; i < indeks; i++) {
			pointer = pointer->next;
		}
		return pointer;
	}
	else {
		return nullptr;
	}
}

element* ListOfPartials::getHead()
{
	return this->head;
}

element* ListOfPartials::getTail()
{
	return this->tail;
}
