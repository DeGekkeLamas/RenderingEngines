#pragma once

#include "iostream"

template<typename T>
struct ListElement {
    ListElement(T value);
    T value;
    ListElement<T>* previous = nullptr;
    ListElement<T>* next = nullptr;
};

template<typename T>
ListElement<T>::ListElement(T value) {
    this->value = value;
}