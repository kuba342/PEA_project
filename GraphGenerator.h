#pragma once
#ifndef GraphGenerator_h
#define GraphGenerator_h

#include "AdjMatrix.h"
#include <iostream>
#include <string>
#include "Additional.h"
#include <Windows.h>

class GraphGenerator
{
public:
	GraphGenerator();
	~GraphGenerator();

	AdjMatrix* generate(AdjMatrix* graph=nullptr);

private:
	int V;
	AdjMatrix* graph;
	void generating();
};

#endif // !GraphGenerator_h
