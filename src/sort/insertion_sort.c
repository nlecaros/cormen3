#include	<stdlib.h>
#include	<stdio.h>
#include    "algorithms.h"

/*
 * Swap first and second positions
 */
void swap(int* first, int* second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

void insertion_sort(int** input, int size) {
    int* data = *input;
    for (int i = 1; i < size; i++) {
        for (int j = i - 1, k = i; j >= 0; j--, k--) {
            if (*(data+k) < *(data+j)) {
                swap((data+k), (data+j)); 
            }
        }
    }
}

