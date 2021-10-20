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

class Menu
{
public:
	Menu();
	~Menu();
	void showMenu();

private:
	AdjMatrix* graph;

	void tests();
	void readData();
	void showGraph();
	void bruteForce();
	void reading();
	void generator();
};

#endif // !Menu_h
