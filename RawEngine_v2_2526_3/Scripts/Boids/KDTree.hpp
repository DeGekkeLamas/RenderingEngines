#pragma once

#include <algorithm>
#include "iostream"

static struct KDTreeHelper {
    // Sorts the array by position
    template<typename T>
    static void SortArray(T* data, const size_t length, int axis = 0) {
        std::sort(data, data + length,
            [axis](const T& a, const T& b) {
                float bValue;
                switch (axis) { // Switch axis used
                    case 0:
                        return a->transform.position().x < b->transform.position().x;
                        break;
                    case 1:
                        return a->transform.position().y < b->transform.position().y;
                        break;
                    case 2:
                        return a->transform.position().z < b->transform.position().z;
                        break;
                }
            });
    };
};

template<typename T>
struct KDTReeElement {
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
        KDTreeHelper::SortArray<T>(boids, numBoids, axis);
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

template<typename T>
class KDTree {
    public:
    ~KDTree() {
        Reset();
    }
    // Reset the KD Tree
    void Reset() const {
        delete root;
    }

    // Create the tree
    void Create(T* data, int length, int depth) {
        Reset();
        // Create root
        root = new KDTReeElement(data, length);
        if (length <= 0) return;
        // Create tree
        int median = length / 2;
        if (depth <= 0) return; // no split if set to 0
        root->SplitAt(median, depth);
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