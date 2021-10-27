#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
	this->lib = new Additional();
}

HeldKarp::~HeldKarp()
{
}

void HeldKarp::calculate() {

}

void HeldKarp::showShortestCycle() {

}