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
#include "ListOfIndividuals.h"

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
	//Populacja
	ListOfIndividuals* population;
	//Individual** population;
	//Wspó³czynniki:
	int populationSize;
	int parentalPopulationSize;
	double crossingFactor;
	double mutationFactor;
	int iterations;

	//Instancja grafu
	AdjMatrix* graph;

	//Najlepsze rozwi¹zanie
	BiList* bestPath;
	int bestWeight;

	//metody
	void generatePopulation();
	void calculateCost(Individual* individual);
	double drawFromTheRange01();
	void updateBestPath(Individual* individual);
};

#endif // !GeneticAlgorithm_h
