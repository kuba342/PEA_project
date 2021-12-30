#pragma once
#ifndef Individual_h
#define Individual_h

#include "BiList.h"
#include "Array.h"


class Individual
{
public:
	Individual(int size);
	~Individual();

	//Settery i gettery
	int getCost();
	int getSize();
	BiList* getPath();

	void setCost(int cost);

private:
	//koszt rozwi�zania
	int cost;
	//Rozmiar �cie�ki - na potrzeby iterowania
	int size;
	//Reprezentacja �cie�kowa
	BiList* path;
};

#endif // !Individual_h
