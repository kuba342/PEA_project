#pragma once
#ifndef Menu_h
#define Menu_h

#include "AdjMatrix.h"

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
	void BruteForce();
	void reading();
};

#endif // !Menu_h
