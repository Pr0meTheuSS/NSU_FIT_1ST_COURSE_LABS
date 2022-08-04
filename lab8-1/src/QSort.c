// Copyright [2022] <Olimpiev Y.>
#include "QSort.h"


void Swap(struct TEdge* left, struct TEdge* right) {
    struct TEdge temp = *left;
    *left = *right;
    *right = temp;
}


void QSort(TEdge* array, size_t amount) {
    assert(array);
    if (amount <= 1) {
        return;
    }
    size_t pivot_index = amount / 2;
    for (size_t i = 0; i < pivot_index; ++i) {
        if (array[i].Weight > array[pivot_index].Weight) {
            // Swap left naighbour of pivot element with bigger element
            Swap(&array[pivot_index - 1], &array[i]);
            // Swap pivot element with bigger
            Swap(&array[pivot_index], &array[pivot_index - 1]);
            pivot_index--;
            i--;
        }
    }
    for (size_t i = pivot_index + 1; i < amount; ++i) {
        if (array[i].Weight < array[pivot_index].Weight) {
            // Swap right naighbour of pivot element with smaller element
            Swap(&array[pivot_index + 1], &array[i]);
            // Swap pivot element with smallee
            Swap(&array[pivot_index], &array[pivot_index + 1]);
            pivot_index++;
            i--;
        }
    }
    // Sort left half
    QSort(array, pivot_index);
    // Sort right half
    QSort(&array[pivot_index], amount - (pivot_index));
}
