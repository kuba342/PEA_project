#pragma once
#ifndef TSPSimulatedAnnealing_h
#define TSPSimulatedAnnealing_h

#include <iostream>
#include <math.h>
#include "AdjMatrix.h"
#include "Array.h"
#include <cstdlib>
#include <ctime>

/*
	Symulowane wy¿arzanie ze schematem ch³odzenia w postaci geometrycznej
*/
class TSPSimulatedAnnealing
{
public:
	TSPSimulatedAnnealing(AdjMatrix* matrix);
	~TSPSimulatedAnnealing();

	void calculate();

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


private:
	AdjMatrix* matrix;
	Array* actualPath;
	int actualPathWeight;
	Array* newPath;
	int newPathWeight;
	Array* bestPath;
	int bestWeight;

	double firstTemp;
	double minimalTemp;
	double currentTemp;
	int iterations;
	int currentIteration;
	double const coolingFactor = 0.999;

	//Algorytm
	void determineFirstSolution();
	void nextSolution();
	void checkConditions();
	void updateBestSolution();
	void updateActualPath();
	void calculateActualPathWeight();
	void calculateNewPathWeight();
	double calculateHeuristic();
	void cooling();
	double drawFromTheRange01();
};

#endif // !TSPSimulatedAnnealing_h
