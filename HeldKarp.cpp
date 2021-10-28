#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->firstTab = nullptr;
	this->secondTab = nullptr;
	this->sizeOfSet = 0;
	this->currentSet = 0;
	this->ListOfNodes = nullptr;
	this->firstTabLength = 0;
	this->SecondTabLength = 0;
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
	this->firstTab = nullptr;
	this->secondTab = nullptr;
	this->sizeOfSet = 0;
	this->currentSet = 0;
	this->ListOfNodes = nullptr;
	this->firstTabLength = 0;
	this->SecondTabLength = 0;
}

HeldKarp::~HeldKarp()
{
}

void HeldKarp::calculate() {
	prepare();
	algorithm();
}

void HeldKarp::showShortestCycle() {

}

void HeldKarp::algorithm()
{
	for (this->sizeOfSet=1; this->sizeOfSet < this->ListOfNodes->getCount(); sizeOfSet++) {
		iteration();
	}
}

//Powinno byæ gotowe
void HeldKarp::prepare() {
	this->ListOfNodes = new BiList();
	for (int i = 1; i < this->matrix->getV(); i++) {
		ListOfNodes->addAtTheEnd(i);
	}

	this->SecondTabLength = 1;
	this->secondTab = new ListOfPartials * [SecondTabLength];
	this->secondTab[0] = new ListOfPartials();

	for (int i = 1; i <= this->ListOfNodes->getCount(); i++) {
		int input = this->matrix->distance(0, i);
		PartialSolution* sol = new PartialSolution(this->matrix, this->sizeOfSet);
		secondTab[0]->addAtTheEnd(*sol);
		secondTab[0]->getElement(i - 1)->solution.setSumOfWeights(input);
		secondTab[0]->getElement(i - 1)->solution.setDestination(i);
		secondTab[0]->getElement(i - 1)->solution.setOneBeforeLast(0);
	}
	this->sizeOfSet++;
}

void HeldKarp::update() {
	this->firstTab = this->secondTab;
	this->firstTabLength = this->SecondTabLength;
	this->SecondTabLength = (int)this->lib->Newton(this->ListOfNodes->getCount(),this->sizeOfSet);
	this->secondTab = new ListOfPartials * [SecondTabLength];
	for (int i = 0; i < SecondTabLength; i++) {
		//Nowo tworzona lista powinna mieæ rozmiar:
		//this->ListOfNodes->getCount() - this->sizeOfSet - 1
		secondTab[i] = new ListOfPartials();
	}
}

void HeldKarp::iteration() {
	update();

	for (currentSet = 0; currentSet < this->firstTabLength; currentSet++) {
		iterationForSet();
	}
}

void HeldKarp::iterationForSet() {
	for (int i = 0; i < firstTab[currentSet]->getSize(); i++) {

		//this->firstTab[currentSet]->getElement(i)->solution.getSet()->addAtTheEnd()
		PartialSolution &list = this->firstTab[currentSet]->getElement(i)->solution;
		//this->firstTab[currentSet]->getElement(i)->solution.getSet()->addAtTheEnd();
		list.getSet()->addAtTheEnd(list.getDestination());
		list.getNodes()->addAtTheEnd(list.getDestination());

		BiList* unusedNodes = new BiList();
		const int n = this->matrix->getV() - 1;
		const int k = list.getNodes()->getCount();

		for (int i = 1; i < this->matrix->getV(); i++) {
			if (list.getSet()->searchKey(i) != -1) {

			}
			else {
				unusedNodes->addAtTheEnd(i);
			}
		}

		for (int j = 0; j < unusedNodes->getCount(); j++) {

		}
	}
}