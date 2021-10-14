#pragma once
#ifndef BiList_h
#define BiList_h

struct listElement {

    listElement* previous;
    int key;
    int weight;
    listElement* next;

};

class BiList
{
private:
    listElement* head;
    listElement* tail;
    int count;

public:
    BiList();
    ~BiList();

    //METODY OPERUJ¥CE NA LIŒCIE
    void addAtTheBeginning(int key, int weight);
    void addAtTheEnd(int key, int weight);
    void addOnPosition(listElement* element, int key, int weight);
    void removeAtTheBeginning();
    void removeAtTheEnd();
    void removeOnPosition(listElement* element);
    void showList();
    int searchKey(int key);

    //SETTERY I GETTERY
    listElement* getElement(int n);
    int getCount();
    listElement* getHead();
    listElement* getTail();
    void setHead(listElement* element);
    void setTail(listElement* element);
};

#endif