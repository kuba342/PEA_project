#pragma once
#ifndef ATSPFileReader_h
#define ATSPFileReader_h

#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include "AdjMatrix.h"

class ATSPFileReader
{
public:
	ATSPFileReader();
	~ATSPFileReader();

	AdjMatrix* readFile(std::string filename);

private:
	int dimension;
	std::string name;
	std::string typeOfEdge;
	std::string edgeFormat;
};

#endif // !ATSPFileReader_h
