#pragma once
#ifndef BiList_h
#define BiList_h

struct listElement {

    listElement* previous;
    int key;
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
    void addAtTheBeginning(int key);
    void addAtTheEnd(int key);
    void addOnPosition(listElement* element, int key);
    void removeAtTheBeginning();
    void removeAtTheEnd();
    void removeOnPosition(listElement* element);
    void showList();
    int searchKey(int key);
    void swap(int beg, int end);
    void reverse(int beg, int end);

    //SETTERY I GETTERY
    listElement* getElement(int n);
    int getCount();
    listElement* getHead();
    listElement* getTail();
    void setHead(listElement* element);
    void setTail(listElement* element);
};

#endif