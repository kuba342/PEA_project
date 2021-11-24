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
	double getCoolingDactor();


private:
	int numberOfCycles;
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
	double const coolingFactor = 0.9999;

	//Algorytm
	void renewParameters();
	void determineFirstSolution();
	void nextSolution();
	void checkConditions(int index);
	void updateBestSolution();
	void updateActualPath(int index);
	void updateNewPath();
	void calculateActualPathWeight();
	void calculateNewPathWeight(int index);
	double calculateHeuristic();
	void cooling();
	double drawFromTheRange01();
};

#endif // !TSPSimulatedAnnealing_h
