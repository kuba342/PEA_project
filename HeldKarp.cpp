#include "HeldKarp.h"

HeldKarp::HeldKarp()
{
	this->matrix = nullptr;
	this->weightOfShortest = INT_MAX;
}

HeldKarp::HeldKarp(AdjMatrix* matrix) {
	this->matrix = matrix;
	this->weightOfShortest = INT_MAX;
}

HeldKarp::~HeldKarp()
{
}

void HeldKarp::calculate() {

}

void HeldKarp::showShortestCycle() {

}