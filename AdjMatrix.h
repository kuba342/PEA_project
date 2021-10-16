#pragma once
#ifndef AdjMatrix_h
#define AdjMatrix_h

/*
	Reprezentacja grafu jako macierz s¹siedztwa
*/
class AdjMatrix
{
private:
	int V;
	int** matrix;

public:
	AdjMatrix();
	AdjMatrix(int V);
	~AdjMatrix();

	bool addEdge(int beg, int end, int weight);
	bool addDirectedEdge(int beg, int end, int weight);

	//Settery i gettery
	int** getMatrix();
	int getV();

	//Reprezentacja grau
	void showGraph();
};

#endif // !AdjMatrix_h
