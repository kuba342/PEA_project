#include "ListOfIndividuals.h"

ListOfIndividuals::ListOfIndividuals()
{
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

ListOfIndividuals::~ListOfIndividuals()
{
	while (this->size) {
		removeAtTheEnd();
	}
}

void ListOfIndividuals::addAtTheEnd(Individual* individual)
{
	elemIn* pointer;
	pointer = new elemIn;
	pointer->individual = individual;
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

void ListOfIndividuals::removeOnPosition(elemIn* elem)
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

	delete elem->individual;
	delete elem;
}

void ListOfIndividuals::removeOnPosition(int indeks)
{
	removeOnPosition(getElement(indeks));
}

void ListOfIndividuals::removeAtTheEnd()
{
	if (this->size) {
		removeOnPosition(this->tail);
	}
}

int ListOfIndividuals::getSize()
{
	return this->size;
}

elemIn* ListOfIndividuals::getElement(int indeks)
{
	elemIn* pointer = this->head;
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

elemIn* ListOfIndividuals::getHead()
{
	return this->head;
}

elemIn* ListOfIndividuals::getTail()
{
	return this->tail;
}

