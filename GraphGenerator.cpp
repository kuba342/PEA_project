#include "GraphGenerator.h"


GraphGenerator::GraphGenerator()
{
	this->V = 0;
	this->graph = nullptr;
}

GraphGenerator::~GraphGenerator()
{
}

void GraphGenerator::generating() {
	int number;
	if (this->V > 0) {
		this->graph = new AdjMatrix(this->V);
		for (int i = 0; i < this->V; i++) {
			for (int j = 0; j < this->V; j++) {
				if (i == j) {
					this->graph->addDirectedEdge(i, j, 0);
				}
				else {
					number = rand()%100;
					this->graph->addDirectedEdge(i,j,number);
				}
			}
		}	
	}
	else {
		system("cls");
		std::cout << "Niepoprawna liczba!";
		Sleep(2000);
		return;
	}
}

AdjMatrix* GraphGenerator::generate(AdjMatrix* graph) {
	this->graph = graph;
	Additional* lib = new Additional();
	std::string bufor;
	std::cout << "Ile wierzcholkow ma miec graf?\n"
			  << "Wprowadz liczbe: ";
	std::cin >> bufor;
	if (lib->isNum(bufor)) {
		this->V = std::stoi(bufor);
		generating();
		return this->graph;
	}
	else {
		system("cls");
		std::cout << "Wprowadzone znaki nie sa liczba!\n"
				  << "Operacja anulowana!";
		Sleep(3000);
		return nullptr;
	}
}