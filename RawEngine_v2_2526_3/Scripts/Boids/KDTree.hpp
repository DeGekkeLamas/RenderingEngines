#pragma once

#include <algorithm>
#include "iostream"


template<typename T>
struct KDTReeElement {
    KDTReeElement() = default;
    ~KDTReeElement() {
        // delete[] elements;
    }
    KDTReeElement(T *boids, int numBoids) {
        this->numBoids = numBoids;
        this->boids = boids;
    }
    // Splits the node into 2 nodes that are added as its elements. Depth determines when to stop splitting
    void SplitAt(int splitIndex, const int depth) {
        splitValue = boids[splitIndex]->transform.position().x;
        elements = new KDTReeElement[2];
        numElements = 2;
        elements[0] = KDTReeElement(boids, splitIndex);
        elements[1] = KDTReeElement(boids + splitIndex, numBoids - splitIndex);

        if (depth <= 0) return; // Stop when threshold met
        elements[0].SplitAt(elements[0].numBoids/2, depth-1);
        elements[1].SplitAt(elements[1].numBoids/2, depth-1);
    }

    KDTReeElement* elements;
    int numElements = 0;
    T* boids;
    int numBoids = 0;
    float splitValue = 0;
};

template<typename T>
class KDTree {
    public:

    // Create the tree
    void Create(T* data, int length, int depth) {
        // Create root
        root = new KDTReeElement(data, length);
        // SortArray<T>(data, length);
        // Create tree
        int median = length / 2;
        root->SplitAt(median, depth);
    }
    // Returns array of all objects in the group target is in, sets size to be the length of that group
    T* FindNeighbours(T target, int& size) {
        KDTReeElement<T>* current = root;
        while (current->numElements != 0) {
            current = &(current->elements[current->splitValue < target->transform.position().x ? 0 : 1]);
        }
        size = current->numBoids;
        return current->boids;
    }
    // Sorts the array by position
    template<typename T>
    static void SortArray(T* data, const size_t length) {
        std::sort(data, data + length,
            [](const T& a, const T& b) {
                return a->transform.position().x < b->transform.position().x;
            });
    };

    private:
    KDTReeElement<T>* root = nullptr;
};