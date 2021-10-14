#pragma once
#ifndef ListGraph_h
#define ListGraph_h

#include "BiList.h"
#include <string>

/**
 * Reprezentacja jako lista nastêpników
 */
class ListGraph
{
private:
    int V;
    int E;
    BiList** table;
    int sumWeights;

public:
    ListGraph();
    ListGraph(int V);
    ~ListGraph();

    bool addEdge(int beg, int end, int weight);
    bool addDirectedEdge(int beg, int end, int weight);

    //Settery i gettery
    BiList* getListFromArray(int indeks);
    int getV();
    int getE();
    int getSumWeights();

    //reprezentacja
    void showGraph();
};

#endif // !ListGraph_h
