#pragma once
#ifndef Array_h
#define Array_h

#include <iostream>

class Array
{
private:
    /* data */
    int* table;
    int size;
public:
    Array();
    Array(int Size);
    ~Array();
    //Settery ii gettery
    int getSize();
    int* getTable();
    void setElement(int index, int element);
    //Operacje na elementach tablicy
    void reverse(int beg, int end);
    void swap(int beginning, int end);
    void addAtTheBeginning(int number);
    void addAtTheEnd(int number);
    void removeAtTheBeginning();
    void removeAtTheEnd();
    void addOnPosition(int number, int numberOfPosition);
    void removeOnPosition(int numberOfPosition);
    void showArray();
    int searchKey(int key);
};

#endif // !Array_h


