#include	<stdlib.h>
#include	<stdio.h>
#include    "algorithms.h"

static void sort(int** input, int p, int q);
static void swap(int** input, int p, int q);
static void merge(int** input, int p, int q, int r);

void merge_sort(int** input, int size) {
    sort(input, 0, size/2);
    sort(input, size/2, size);
    merge(input, 0, size/2, size);
}

static void sort(int** input, int p, int q) {
    // one element: do nothing
    if (p+1 == q) {
       return;
    }
    // two elements: swap if out of order
    if (p+2 == q) {
        if (*(*input+p) > *(*input+q)) {
            swap(input, p, q);
        }
    } else {
        sort(input, p, (p+q)/2);
        sort(input, (p+q)/2, q);
        merge(input, p, (p+q)/2, q);
    }
}

/*
 * i and j are indexes into elements in input
 * When this method returns, the contents of 
 * i and j have been exchanged
 */
static void swap(int** input, int p, int q) {
    int temp = *(*input+p);
    *(*input+p) = *(*input+q);
    *(*input+q) = temp;
}

/*
 * p, q, and r are indexes into input such 
 * that p <= q <= r
 * Entries in the range p to q-1 are sorted
 * Entries in the range q to r are sorted
 * When this method returns, elements in
 * the input from p to r are in sorted order
 */
static void merge(int** input, int p, int q, int r) {
    // TODO: implement this!
}


