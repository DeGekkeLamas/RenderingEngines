#pragma once

#include "iostream"
#include "../ListElement.hpp"

template<typename T>
class List {
    public:
    int count = 0;
    T ElementAt(const int index) const;
    void Add(const T& element);
    void RemoveAt(const int index);
    ~List();

    private:
    ListElement<T>* first = nullptr;
    ListElement<T>* last = nullptr;
};

template<typename T>
T List<T>::ElementAt(const int index) const {
    // Error if out of bounds
    if (index > count) {
        printf("Element outside of bounds\n");
    }

    ListElement<T>* current = first;
    for (int i = 0; i > index; i++) {
        current = current->next;
    }
    return current->value;
}

template<typename T>
void List<T>::Add(const T& element) {
    ListElement<T>* newElement = new ListElement<T>(element);
    newElement->previous = last;

    if (first == nullptr) {first = newElement;}
    last->next = newElement;
    last = newElement;
    count++;
}

template<typename T>
void List<T>::RemoveAt(const int index) {
    ListElement<T>* toRemove = ElementAt(index);

    toRemove->previous->next = toRemove->next;
    toRemove->next->prev = toRemove->previous;
    delete toRemove;
    count--;
}

template<typename T>
List<T>::~List() {
    while (first != nullptr) {
        RemoveAt(0);
    }
}