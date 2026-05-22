#pragma once

#include <algorithm>
#include <functional>

#include "iostream"

template<typename T>
using comparer = std::function<bool(const T&,const T&)>;

static struct KDTreeHelper {
    // Sorts the array by position
    template<typename T>
    static void SortArray(T* data, const size_t length, int axis,
        comparer<T> compareX, comparer<T> compareY, comparer<T> compareZ) {
        std::sort(data, data + length,
            [axis, compareX, compareY, compareZ](const T& a, const T& b) {
                switch (axis) { // Switch axis used
                    case 0:
                        return compareX(a,b);
                    case 1:
                        return compareY(a,b);
                    case 2:
                        return compareZ(a,b);
                }
            });
    };
};

template<typename T>
struct KDTReeElement {
    // Compare functions for sorting the array
    static comparer<T> compareX;
    static comparer<T> compareY;
    static comparer<T> compareZ;

    KDTReeElement() = default;
    ~KDTReeElement() {
        delete[] elements;
    }
    KDTReeElement(T *boids, int numBoids) {
        this->numBoids = numBoids;
        this->boids = boids;
    }
    // Splits the node into 2 nodes that are added as its elements. Depth determines when to stop splitting
    void SplitAt(int splitIndex, const int depth) {
        axis = depth % 3;
        KDTreeHelper::SortArray<T>(boids, numBoids, axis, compareX, compareY, compareZ); // TODO: compares
        // Change split value based on axis used
        switch (axis) {
            case 0:
                splitValue = boids[splitIndex]->transform.position().x;
                break;
            case 1:
                splitValue = boids[splitIndex]->transform.position().y;
                break;
            case 2:
                splitValue = boids[splitIndex]->transform.position().z;
                break;
        }
        elements = new KDTReeElement[2];
        numElements = 2;
        // Creating subnodes
        elements[0] = KDTReeElement(boids, splitIndex);
        elements[1] = KDTReeElement(boids + splitIndex, numBoids - splitIndex);

        // Stop when threshold met
        if (depth <= 1) return;
        elements[0].SplitAt(elements[0].numBoids/2, depth-1);
        elements[1].SplitAt(elements[1].numBoids/2, depth-1);
    }

    KDTReeElement* elements = nullptr;
    int numElements = 0;
    int axis = 0;
    T* boids;
    int numBoids = 0;
    float splitValue = 0;
};

template<typename T> comparer<T> KDTReeElement<T>::compareX;
template<typename T> comparer<T> KDTReeElement<T>::compareY;
template<typename T> comparer<T> KDTReeElement<T>::compareZ;

template<typename T>
class KDTree {
    public:
    ~KDTree() {
        Reset();
    }
    // Reset the KD Tree
    void Reset() {
        delete root;
    }

    // Create the tree
    void Create(T* data, int length, int depth) {
        Reset();
        // Create root
        root = new KDTReeElement<T>(data, length);
        if (length <= 0) return;
        // Create tree
        int median = length / 2;
        if (depth <= 0) return; // no split if set to 0
        root->SplitAt(median, depth);
    }

    // Used to set compares used to sort the tree
    void SetComparisons(comparer<T> X, comparer<T> Y, comparer<T> Z) {
        KDTReeElement<T>::compareX = X;
        KDTReeElement<T>::compareY = Y;
        KDTReeElement<T>::compareZ = Z;
    }

    // Returns array of all objects in the group target is in, sets size to be the length of that group
    T* FindNeighbours(T target, int& size) {
        KDTReeElement<T>* current = root;
        while (current->numElements != 0) {
            // Change split value based on axis used
            float targetValue;
            switch (current->axis) {
                case 0:
                    targetValue = target->transform.position().x;
                    break;
                case 1:
                    targetValue = target->transform.position().y;
                    break;
                case 2:
                    targetValue = target->transform.position().z;
                    break;
            }
            current = &(current->elements[current->splitValue > targetValue ? 0 : 1]);
        }
        size = current->numBoids;
        return current->boids;
    }

    private:
    KDTReeElement<T>* root = nullptr;
};