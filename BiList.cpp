#include "BiList.h"
#include <iostream>

//KONSTRUKTOR
BiList::BiList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

//DESTRUKTOR
BiList::~BiList() {
    while (this->count) {
        this->removeAtTheEnd();
    }
}


/*********METODY OPERUJ�CE NA LI�CIE**********/
void BiList::addAtTheBeginning(int key, int weight) {
    listElement* pointer;
    //Nowy element
    pointer = new listElement;
    //Wpisuje dane do nowego elementu
    pointer->key = key;
    pointer->weight = weight;
    //Nowy element nie ma poprzednika
    pointer->previous = nullptr;
    //W pole next wpisuj� adres czo�a listy
    pointer->next = this->head;
    //W polu head listy umieszczam adres nowego elementu
    this->head = pointer;
    //Zwi�kszam licznik element�w o 1
    this->count++;
    //Sprawdzam czy istnieje nast�pnik czo�a listy i w jego pole previous wpisuj�
    //adres dodawanego elementu
    if (pointer->next) {
        pointer->next->previous = pointer;
    }
    else {
        this->tail = pointer;   //Je�li nie ma nast�pnika, to nowy element jest tak�e ogonem.
    }
}

void BiList::addAtTheEnd(int key, int weight) {
    listElement* pointer;
    //Nowy element
    pointer = new listElement;
    //Dane dla nowego elementu
    pointer->key = key;
    pointer->weight = weight;
    //W pole next adres zerowy, bo nie ma nast�pnika
    pointer->next = nullptr;
    //W pole previous zawarto�� pola tail - poprzednik tworzonego elementu
    pointer->previous = this->tail;
    //Do pola tail wpisuj� adres tworzonego elementu
    this->tail = pointer;
    //Zwi�kszam licznik o 1
    this->count++;
    //Sprawdzam czy istnieje poprzednik, je�li nie, wpisuj� do czo�a nowy element
    if (pointer->previous) {
        pointer->previous->next = pointer;
    }
    else {
        this->head = pointer;
    }
}

//Dodaj element przed wybranym
void BiList::addOnPosition(listElement* element, int key, int weight) {
    listElement* pointer;
    //Je�li element jest czo�em, dodaj na pocz�tek listy
    if (element == this->head) {
        this->addAtTheBeginning(key, weight);
    }
    else {
        pointer = new listElement;
        //Wpisuj� dane
        pointer->key = key;
        pointer->weight = weight;
        //Nast�pnik to element podany
        pointer->next = element;
        //Poprzednikiem jest poprzednik wskazanego elementu
        pointer->previous = element->previous;

        this->count++;

        //ustawiam w poprzedniku nast�pnika jako nowy element
        element->previous->next = pointer;
        //Ustawiam w nast�pniku poprzednik - nowy element
        element->previous = pointer;
    }
}

void BiList::removeAtTheBeginning() {
    if (this->count) {
        removeOnPosition(this->head);
    }
}

void BiList::removeAtTheEnd() {
    if (this->count) {
        removeOnPosition(this->tail);
    }
}

void BiList::removeOnPosition(listElement* element) {
    //Zmniejszam licznik listy
    this->count--;

    //Je�li istnieje poprzednik, to jako nast�pnik przypisuj� mu 
    //nast�pnika usuwanego elementu
    if (element->previous) {
        element->previous->next = element->next;
    }
    else {
        this->head = element->next;     //W przeciwnym razie do czo�a przypisuj� nast�pnik
    }

    //Je�li element posiada nast�pnik, to w jego pole poprzednika wpisuj� poprzednika
    //usuwanego elementu. W przypadku ogona wpisuj� poprzednik usuwanego elementu
    if (element->next) {
        element->next->previous = element->previous;
    }
    else {
        this->tail = element->previous;
    }

    delete element;
}

//ZROBI� ZABEZPIECZENIE PRZED PUST� LIST� W OPERACJACH!
void BiList::showList() {
    listElement* pointer;
    pointer = this->head;

    std::cout << "List: [";
    for (pointer; pointer != nullptr; pointer = pointer->next) {
        std::cout << "  " << pointer->key << ":(" << pointer->weight << ")  ";
    }
    std::cout << "]";
}

int BiList::searchKey(int key) {
    int count = 0;
    for (listElement* i = this->head; i != this->tail->next; i = i->next) {
        if (i->key == key) {
            return count;
        }
        count++;
    }
    return -1;
}

/*********SETTERY I GETTERY*******************/
listElement* BiList::getElement(int n) {
    listElement* pointer = this->head;
    if (n <= this->count) {
        for (int i = 0; i < n; i++) {
            pointer = pointer->next;
        }
        return pointer;
    }
    else {
        return nullptr;
    }
}

int BiList::getCount() {
    return this->count;
}

listElement* BiList::getHead() {
    return this->head;
}

listElement* BiList::getTail() {
    return this->tail;
}

void BiList::setHead(listElement* element) {
    this->head = element;
}

void BiList::setTail(listElement* element) {
    this->tail = element;
}