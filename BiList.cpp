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


/*********METODY OPERUJ¥CE NA LIŒCIE**********/
void BiList::addAtTheBeginning(int key, int weight) {
    listElement* pointer;
    //Nowy element
    pointer = new listElement;
    //Wpisuje dane do nowego elementu
    pointer->key = key;
    pointer->weight = weight;
    //Nowy element nie ma poprzednika
    pointer->previous = nullptr;
    //W pole next wpisujê adres czo³a listy
    pointer->next = this->head;
    //W polu head listy umieszczam adres nowego elementu
    this->head = pointer;
    //Zwiêkszam licznik elementów o 1
    this->count++;
    //Sprawdzam czy istnieje nastêpnik czo³a listy i w jego pole previous wpisujê
    //adres dodawanego elementu
    if (pointer->next) {
        pointer->next->previous = pointer;
    }
    else {
        this->tail = pointer;   //Jeœli nie ma nastêpnika, to nowy element jest tak¿e ogonem.
    }
}

void BiList::addAtTheEnd(int key, int weight) {
    listElement* pointer;
    //Nowy element
    pointer = new listElement;
    //Dane dla nowego elementu
    pointer->key = key;
    pointer->weight = weight;
    //W pole next adres zerowy, bo nie ma nastêpnika
    pointer->next = nullptr;
    //W pole previous zawartoœæ pola tail - poprzednik tworzonego elementu
    pointer->previous = this->tail;
    //Do pola tail wpisujê adres tworzonego elementu
    this->tail = pointer;
    //Zwiêkszam licznik o 1
    this->count++;
    //Sprawdzam czy istnieje poprzednik, jeœli nie, wpisujê do czo³a nowy element
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
    //Jeœli element jest czo³em, dodaj na pocz¹tek listy
    if (element == this->head) {
        this->addAtTheBeginning(key, weight);
    }
    else {
        pointer = new listElement;
        //Wpisujê dane
        pointer->key = key;
        pointer->weight = weight;
        //Nastêpnik to element podany
        pointer->next = element;
        //Poprzednikiem jest poprzednik wskazanego elementu
        pointer->previous = element->previous;

        this->count++;

        //ustawiam w poprzedniku nastêpnika jako nowy element
        element->previous->next = pointer;
        //Ustawiam w nastêpniku poprzednik - nowy element
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

    //Jeœli istnieje poprzednik, to jako nastêpnik przypisujê mu 
    //nastêpnika usuwanego elementu
    if (element->previous) {
        element->previous->next = element->next;
    }
    else {
        this->head = element->next;     //W przeciwnym razie do czo³a przypisujê nastêpnik
    }

    //Jeœli element posiada nastêpnik, to w jego pole poprzednika wpisujê poprzednika
    //usuwanego elementu. W przypadku ogona wpisujê poprzednik usuwanego elementu
    if (element->next) {
        element->next->previous = element->previous;
    }
    else {
        this->tail = element->previous;
    }

    delete element;
}

//ZROBIÆ ZABEZPIECZENIE PRZED PUST¥ LIST¥ W OPERACJACH!
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