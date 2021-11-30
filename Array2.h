#pragma once
#ifndef SDIZO_1_ARRAY_H
#define SDIZO_1_ARRAY_H
#include <memory>
#include <string>
#include <functional>
//#include "ArrayIterator.h"
//#include "../OrderedCollection.h"

//szablon klasy implementuj¹cej tablicê dynamiczn¹
template <typename T>
class Array2 : public OrderedCollection<T>
{
public:
    Array2<T>();
    explicit Array2<T>(size_t initialSize);
    void putAtPosition(T, const size_t);
    void swap(const size_t, const size_t);
    T removeAt(const size_t index);
    void pushBack(T);
    bool contains(T element);
    void pushFront(T);
    T removeLast();
    T removeFirst();
    T get(const size_t index);
    bool isEmpty();
    [[nodiscard]] size_t getLength() const;
    std::string toString();
    T& operator[](size_t) const;
    size_t forEach(std::function<bool(T&)>);
    T& find(std::function<bool(T)> condition);

    //ArrayIterator<T> iterator();
private:
    std::shared_ptr<T[]> elements;
    size_t length;
};

//wyj¹tek oznaczaj¹cy ¿¹danie elementu o indeksie niebêd¹cym w tablicy
class IndexOutOfBoundException : public std::exception
{
public:
    char const* what() const override {
        return message;
    };
private:
    constexpr static const char message[] = "Index out of bound exception";
};


template <typename T>
Array2<T>::Array2()
{
    length = 0;
    elements = std::shared_ptr<T[]>(new T[length]);
}

//metoda do dodania elementu na koñcu
template<typename T>
void Array2<T>::pushBack(T element)
{
    putAtPosition(element, length);
}

//metoda do usuniêcia elementu na pocz¹tku
template <typename T>
T Array2<T>::removeFirst()
{
    return removeAt(0);
}

//metoda usuwaj¹ca ostatni element
template <typename T>
T Array2<T>::removeLast()
{
    return removeAt(length - 1);
}

//metoda dodaj¹ca element na pocz¹tku tablicy
template <typename T>
void Array2<T>::pushFront(T element)
{
    putAtPosition(element, 0);
}

//metoda zwracaj¹ca element o danym indeksie przez wartoœæ
template <typename T>
T Array2<T>::get(const size_t index)
{
    if (index >= length)
        throw IndexOutOfBoundException();
    return elements[index];
}

//metoda do usuwania elementu po indeksie
template <typename T>
T Array2<T>::removeAt(const size_t index)
{
    auto buffer = elements[index];
    auto newArray = std::shared_ptr<T[]>(new T[length - 1]);
    for (size_t i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for (size_t i = index + 1; i < length; i++)
    {
        newArray[i - 1] = elements[i];
    }
    elements = newArray;
    length--;
    return buffer;
}

//metoda do zamiany dwóch elementów miejscami
template<typename T>
void Array2<T>::swap(const size_t index1, const size_t index2)
{
    const auto buffer = elements[index1];
    elements[index1] = elements[index2];
    elements[index2] = buffer;
}

//metoda wstawiaj¹ca nowy element na danej pozycji
template<typename T>
void Array2<T>::putAtPosition(T element, const size_t index)
{
    if (index > length)
    {
        throw IndexOutOfBoundException();
    }
    auto newArray = std::shared_ptr<T[]>(new T[length + 1]);
    for (size_t i = 0; i < index; i++)
    {
        newArray[i] = elements[i];
    }
    for (size_t i = index; i < length; i++)
    {
        newArray[i + 1] = elements[i];
    }
    newArray[index] = element;
    elements = std::move(newArray);
    length++;
}

template <typename T>
bool Array2<T>::isEmpty()
{
    return !length;
}

template <typename T>
size_t Array2<T>::getLength() const
{
    return length;
}

template <typename T>
std::string Array2<T>::toString()
{
    std::string output = "[";
    if (length)
    {
        output += std::to_string(elements[0]);
    }
    for (size_t i = 1; i < length; i++)
    {
        output += ", " + std::to_string(elements[i]);
    }
    output += "]";
    return output;
}

template<typename T>
bool Array2<T>::contains(T element) {
    for (size_t i = 0; i < length; i++)
    {
        if (element == elements[i])
        {
            return true;
        }
    }
    return false;
}

//metoda pozwalaj¹ca stworzyæ tablicê zadanej wielkoœci;
//zaimplementowana aby umo¿liwiæ szybsze budowanie struktury
//z pliku i generowanie du¿ych tablic do testów
template<typename T>
Array2<T>::Array2(size_t initialSize) {
    length = initialSize;
    elements = std::shared_ptr<T[]>(new T[initialSize]);
}

//operator dostêpu do elementu po indeksie;
//zwraca obiekt przez referencjê, dzia³anie jak
//ten sam operator dla tablicy
template<typename T>
T& Array2<T>::operator[](size_t index) const {
    if (index >= length)
        throw IndexOutOfBoundException();
    return elements[index];
}

template<typename T>
size_t Array2<T>::forEach(std::function<bool(T&)> function) {
    size_t count{};
    for (size_t i = 0; i < length; i++) {
        if (function(elements[i]))
            count++;
    }
    return count;
}

template<typename T>
T& Array2<T>::find(std::function<bool(T)> condition) {
    for (size_t i = 0; i < length; i++) {
        if (condition(elements[i]))
            return elements[i];
    }
    throw std::exception();
}


#endif //SDIZO_1_ARRAY_H