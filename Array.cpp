#include "Array.h"

/*KONSTRUKTORY*/
Array::Array() {
    this->size = 0;
    this->table = nullptr;
}
Array::Array(int Size) {
    this->size = Size;
    this->table = new int[Size];
}

/*DESTRUKTOR*/
Array::~Array()
{
    delete[] table;
}

/*METODY POMOCNICZE*/
//Zamieñ dwie wartoœci w tablicy
void Array::swap(int beginning, int end) {
    int bufor;
    if (beginning > this->size || end > this->size) {
        std::cout << "Nieprawidlowe indeksy";
        return;
    }
    else {
        bufor = this->table[beginning];
        this->table[beginning] = this->table[end];
        this->table[end] = bufor;
    }
}

void Array::reverse(int beg, int end) {
    while (beg != end) {
        swap(beg, end);
        beg++;
        if (beg == end) {
            return;
        }
        else {
            end--;
        }
    }
}

void Array::addAtTheBeginning(int number) {
    this->size++;
    int* Tab;
    Tab = new int[size];
    Tab[0] = number;
    for (int i = 1; i < size; i++) {
        Tab[i] = this->table[i - 1];
    }
    delete[] table;
    this->table = Tab;
}

void Array::addAtTheEnd(int number) {
    this->size++;
    int* Tab;
    Tab = new int[size];
    Tab[size - 1] = number;
    for (int i = 0; i < size - 1; i++) {
        Tab[i] = this->table[i];
    }
    delete[] table;
    this->table = Tab;
}

void Array::removeAtTheBeginning() {
    this->size--;
    int* Tab;
    Tab = new int[size];
    for (int i = 0; i < size; i++) {
        Tab[i] = this->table[i + 1];
    }
    delete[] table;
    this->table = Tab;
}

void Array::removeAtTheEnd() {
    this->size--;
    int* Tab;
    Tab = new int[size];
    for (int i = 0; i < size; i++) {
        Tab[i] = this->table[i];
    }
    delete[] table;
    this->table = Tab;
}

//Metoda, która nie usuwa danych lecz dodaje nowe "pomiêdzy"
void Array::addOnPosition(int number, int numberOfPosition) {
    this->size++;
    int* Tab;
    Tab = new int[size];
    for (int i = 0; i < this->size; i++) {
        if (i < numberOfPosition) {
            Tab[i] = this->table[i];
        }
        else if (i == numberOfPosition) {
            Tab[i] = number;
        }
        else {
            Tab[i] = this->table[i - 1];
        }
    }
    delete[] table;
    this->table = Tab;
}

void Array::removeOnPosition(int numberOfPosition) {
    this->size--;
    int* Tab;
    Tab = new int[size];
    for (int i = 0; i < this->size; i++) {
        if (i >= numberOfPosition) {
            Tab[i] = this->table[i + 1];
        }
        else {
            Tab[i] = this->table[i];
        }
    }
    delete[] table;
    this->table = Tab;
}

void Array::showArray() {
    printf("Zawartosc tablicy: [");
    for (int i = 0; i < this->size; i++) {
        printf(" %d ", this->table[i]);
    }
    printf("]\n");
}

int Array::searchKey(int key) {
    for (int i = 0; i < this->size; i++) {
        if (this->table[i] == key) {
            return i;
        }
    }
    return -1;  //Jeœli -1, to nie wystêpuje
}

/*SETTERY I GETTERY*/
int Array::getSize() {
    return this->size;
}

int* Array::getTable() {
    return this->table;
}

void Array::setElement(int index, int element) {
    this->table[index] = element;
}