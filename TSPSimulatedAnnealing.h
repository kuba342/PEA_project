#pragma once
#ifndef TSPSimulatedAnnealing_h
#define TSPSimulatedAnnealing_h

#include <iostream>
#include "AdjMatrix.h"
#include "Array.h"

/*
	Symulowane wy¿arzanie ze schematem ch³odzenia w postaci geometrycznej
*/
class TSPSimulatedAnnealing
{
public:
	TSPSimulatedAnnealing();
	TSPSimulatedAnnealing(AdjMatrix* matrix);
	~TSPSimulatedAnnealing();
	void prepare();

private:
	AdjMatrix* matrix;
	Array* actualPath;
	Array* bestPath;
	int bestWeight;
	double firstTemp;
	double minimalTemp;
	double currentTemp;
	int iterations;
	int currentIteration;
	double const coolingFactor;



	//Settery i gettery
	void setFirstTemp(double temp);
	void setminimalTemp(double temp);
	void setIterations(int iterations);
	
	Array* getActualPath();
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
