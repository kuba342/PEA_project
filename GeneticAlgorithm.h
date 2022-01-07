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
	void setVersion(bool version);

	BiList* getBestPath();
	int getBestWeight();

private:
	//Populacja
	ListOfIndividuals* population;
	//Wyselekcjonowani rodzice
	ListOfIndividuals* parents;
	//Dzieci po skrzy¿owaniu - jeœli do tego dosz³o
	ListOfIndividuals* children;	//Liczba dzieci bêdzie zale¿eæ od wspó³czynnika krzy¿owania
	//Wspó³czynniki:
	int populationSize;
	int tournamentParticipants;
	double crossingFactor;
	double mutationFactor;
	int iterations;

	//Instancja grafu
	AdjMatrix* graph;

	//Wariant mutacji
	bool version;

	//Najlepsze rozwi¹zanie
	BiList* bestPath;
	int bestWeight;

	//metody
	void nextGeneration();
	void chooseParents();
	void showPopulation();
	void showParents();
	void showChildren();
	void crossing();
	void mutation();
	void PMXCrossover(Individual* parent1, Individual* parent2);
	bool isInPath(int value, int beg, int end, Individual* ind);
	void inversionMutation(Individual* individual);
	void exchangeMutation(Individual* individual);
	void generatePopulation();
	void calculateCost(Individual* individual);
	double drawFromTheRange01();
	void updateBestPath(Individual* individual);
};

#endif // !GeneticAlgorithm_h
