#pragma once
#ifndef GeneticAlgorithm_h
#define GeneticAlgorithm_h

#include <iostream>
#include "AdjMatrix.h"
#include "Array.h"
#include "BiList.h"
#include <cstdlib>
#include <ctime>
#include "Individual.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(AdjMatrix* matrix);
	~GeneticAlgorithm();

	void calculate();
	void showBestCycle();

	//Settery i gettery
	void setPopulationSize(int size);
	int getPopulationSize();
	void setCrossingFactor(double factor);
	double getCrossingFactor();
	void setMutationFactor(double factor);
	double getMutationFactor();
	void setIterations(int iterations);

	BiList* getBestPath();
	int getBestWeight();

private:
	//Wsp�czynniki:
	int populationSize;
	double crossingFactor;
	double mutationFactor;
	int iterations;

	//Instancja grafu
	AdjMatrix* graph;

	//Najlepsze rozwi�zanie
	BiList* bestPath;
	int bestWeight;

	//metody
	void generatePopulation();
	double drawFromTheRange01();
	void updateBestPath(Individual* individual);
};

#endif // !GeneticAlgorithm_h