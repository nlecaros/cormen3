#include	<stdlib.h>
#include	<stdio.h>
#include    "algorithms.h"

void insertion_sort(int** input, int size) {
    int *data = *input;
    for (int j = 1; j < size; j++) {
        int key = *(data+j);
        int i = j - 1;
        while (i >= 0 && *(data+i) > key) {
            *(data+i+1) = *(data+i);
            i--;
        }
        *(data+i+1) = key;
    }
}

