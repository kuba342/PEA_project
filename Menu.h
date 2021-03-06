#pragma once
#ifndef Menu_h
#define Menu_h

#include "AdjMatrix.h"
#include <iostream>
#include <Windows.h>
#include "AdjMatrix.h"
#include "ATSPFileReader.h"
#include <fstream>
#include "GraphGenerator.h"
#include "BruteForce.h"
#include "HeldKarp.h"
#include "BranchAndBound.h"
#include "Additional.h"
#include <string>
#include "clock.h"
#include "TSPSimulatedAnnealing.h"
#include "TabuSearch.h"
#include "GeneticAlgorithm.h"

class Menu
{
public:
	Menu();
	~Menu();
	void showMenu();

private:
	AdjMatrix* graph;
	BruteForce* brut;
	HeldKarp* held;
	BranchAndBound* branch;
	TSPSimulatedAnnealing* sa;
	TabuSearch* tabu;
	GeneticAlgorithm* genetic;
	Additional* lib;
	Clock* clock;

	void tests();
	void generateResults(char decision, int v);
	void readData();
	void showGraph();
	void bruteForce();
	void heldKarp();
	void reading();
	void generator();
	void BnB();
	void simulatedAnnealing();
	void saParameters();
	void tabuSearch();
	void tabuParameters();
	void geneticAlgorithm();
	void geneticParameters();
};

#endif // !Menu_h
