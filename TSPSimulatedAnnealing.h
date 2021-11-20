#pragma once
#ifndef TSPSimulatedAnnealing_h
#define TSPSimulatedAnnealing_h

#include <iostream>
#include <math.h>
#include "AdjMatrix.h"
#include "Array.h"

/*
	Symulowane wy¿arzanie ze schematem ch³odzenia w postaci geometrycznej
*/
class TSPSimulatedAnnealing
{
public:
	TSPSimulatedAnnealing(AdjMatrix* matrix);
	~TSPSimulatedAnnealing();

private:
	AdjMatrix* matrix;
	Array* actualPath;
	int actualPathWeight;
	Array* bestPath;
	int bestWeight;

	double firstTemp;
	double minimalTemp;
	double currentTemp;
	int iterations;
	int currentIteration;
	double const coolingFactor = 0.99;

	//Algorytm
	void prepare();
	void determineFirstSolution();
	void calculateActualPathWeight();
	double calculateHeuristic();
	void cooling();


	//Settery i gettery
	void setFirstTemp(double temp);
	void setminimalTemp(double temp);
	void setIterations(int iterations);
	
	Array* getActualPath();
	int getActualPathWeight();
	Array* getBestPath();
	int getBestWeight();
	double getFirstTemp();
	double getMinimalTemp();
	double getcurrentTemp();
	int getIterations();
	int getCurrentIteration();
	double getCoolingDactor();
};

#endif // !TSPSimulatedAnnealing_h
