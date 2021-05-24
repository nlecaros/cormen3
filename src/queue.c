#include <stdio.h>

#define QUEUE_SIZE 10

struct queue {
    int head;
    int tail;
    int elements[QUEUE_SIZE];
};

static int empty(const struct queue q) {
    return q.head == q.tail;
}

static void print(const struct queue q) {
    if (empty(q)) {
        printf("%s\n", "[]");
        return;
    }
    int head = q.head;
    int tail = q.tail;
    printf("%s", "[ ");
    while (head < tail) {
        printf("%d ", q.elements[head++ % QUEUE_SIZE]);
    }
    printf("%s\n", "]");
}

static int full(const struct queue q) {
    return q.tail - q.head == QUEUE_SIZE;
}

static void enqueue(struct queue* q, int element) {
    if (full(*q)) {
        return;
    }
    q->tail = q->tail + 1;
    q->elements[(q->tail - 1) % QUEUE_SIZE] = element;
} 

static int dequeue(struct queue* q) {
    if (empty(*q)) {
        return;
    }
    q->head = q->head + 1;
    return q->elements[((q->head - 1) % QUEUE_SIZE)];
}

static void init_queue(struct queue* q) {
    q->head = 0;
    q->tail = 0;
}

/*
 * TODO: modify to take queue size as input
 */
int main(int argc, char** argv) {
    struct queue q;
    init_queue(&q);    
    int input[] = { 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25 };
    int i = 0;
    int sz = sizeof(input) / sizeof(int);
    for (i = 0; i < sz; i++) {
        enqueue(&q, input[i]);
        print(q);
    }
    while (!empty(q)) {
        dequeue(&q);
        print(q);
    }
}

