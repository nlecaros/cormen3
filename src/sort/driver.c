/*
 * Driver program to benchmark different sorting algorithms
 */
#include    <stdio.h>
#include    <stdlib.h>
#include    "algorithms.h"

#define     MAX_LINE    80

static void usage(char* s);
static int read_ints(int** integers);
static void print_ints(int* integers, int num);

int main(int argc, char** argv) {
    if (argc < 2) {
        usage(argv[0]);
        exit(0);
    }
    int* data;
    int num = read_ints(&data);
    print_ints(data, num);
    free(data);
}

static void usage(char* s) {
    printf("Usage: %s <sorting-algorithm>\n", s);
    printf("    input from stdin and output from stdout\n");
}

/*
 * integers - pointer to pointer of integers for
 *            which memory needs to be allocated.
 *            will contain the integers read on
 *            function return
 * returns    the number of integers read
 */
static int read_ints(int** integers) {
    /*
     * Allocate an initial block of memory to hold the ints and hold in a temp pointer
     * Read ints until no more ints can be read or memory block is full
     * If memory block is full, reallocate by doubling the memory block size
     *      If reallocate failed, release previously allocated memory block and return failure
     *      If reallocate succeeded, continue reading ints
     * If no more ints, free unused memory by reallocating and assign location pointed
     *      to by temp pointer to pointer argument
     */
    int allocated = 1000; // Initial slots to allocate
    int used = 0; // number of slots actually used
    int* ints = malloc(allocated * sizeof(int));
    if (!ints) {
        perror("Could not allocate memory");
        exit(-1);
    }

    // offset to memory location to hold the next int
    // if this doesn't change, then no int was read
    int i = 0; 
    // temporary placeholder for int conversions
    int candidate; 
    // buffer to hold the next candidate int
    char buffer[MAX_LINE];
    // temporary holder for reallocated block
    int *temp = NULL;
    while (NULL != (fgets(buffer, MAX_LINE, stdin))) {
        int candidate = strtod(buffer, NULL);
        if (candidate == 0) { // couldn't convert to an int
            continue;
        }
        *(ints+i) = candidate;
        i++;
        used++;
        // We're out of slots.  Get some more, if possible.
        if (i == allocated) {
            temp = realloc(ints, allocated * 2 * sizeof(int)); // Let's double it.
            if (temp) {
                free(ints); // free previously allocated memory
                ints = temp;
                allocated *= 2;
            } else { // Couldn't get more.  Free whatever we still have and bail.
                free(ints);
                perror("Could not reallocate more memory");
                exit(-1);
            }
        }
    }
    if (i == 0) { // We never read any ints
        free(ints);
    } else if (i < allocated) { // We read less ints than for which we allocated
        *integers = realloc(ints, i * sizeof(int));
        // Failed to shrink, use the original pointer unchanged.
        if (!*integers) { 
            *integers = ints;
        }
    }
    return i;
}

static void print_ints(int* integers, int num) {
    for (int i = 0; i < num; i++) {
        printf("%d\n", *(integers+i));
    }
}

