#pragma once

// #include "BoidObject.hpp" // TODO: circular dependency to fix
#include <algorithm>

#include "iostream"


template<typename T>
struct KDTReeElement {
    KDTReeElement() = default;

    ~KDTReeElement() {
        delete[] elements;
    }
    KDTReeElement(T *boids, int numBoids) {
        this->numBoids = numBoids;
        this->boids = boids;
        elements = new KDTReeElement[2];
    }
    KDTReeElement* elements;
    T* boids;
    int numBoids;
};

template<typename T>
class KDTree {
    public:
    int depth = 0;

    void Create(T* data, int length) {
        // Create root
        root = new KDTReeElement(data, length / 2);
        // Create tree
        for (int i = 0; i < depth; i++) {
            SortArray(data, length);
            int median = length / 2;

            root->elements[0].numBoids = median;
            root->elements[1].numBoids = median%2==0 ? median : median-1;
            root->elements[1].boids += root->elements[1].numBoids * sizeof(T);
        }
    }

    T FindNeighbours(T target, int& size) {
        return target;
    }
    template<typename T>
    static void SortArray(T* data, size_t length) {
        std::sort(data, data + length * sizeof(T),
            [](T* a, T* b) {return a->transform.position().x < b->transform.position().x;});
    };

    private:
    KDTReeElement<T>* root = nullptr;
};