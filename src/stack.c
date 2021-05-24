#include <stdio.h>

#define STACK_SIZE 10

struct stack {
    int top;
    int elements[STACK_SIZE];
};

static int full(struct stack s) {
    return s.top == STACK_SIZE;
}

static int empty(const struct stack s) {
    return s.top == 0;
}

static void print(const struct stack s) {
    if (empty(s)) {
        printf("%s\n", "[]");
        return;
    }
    int i;
    printf("%s","[ ");
    for (i = 0; i < s.top; i++) {
        printf("%d ", s.elements[i]);
    }
    printf("%s\n","]");
}

static void push(struct stack *s, int element) {
    if (!full(*s)) {
        s->elements[(s->top)++] = element;
    }
}

static int pop(struct stack *s) { 
    return empty(*s) ? 0 : s->elements[--(s->top)];
}

static void init_stack(struct stack *s) {
    s->top = 0;
}

/*
 * TODO: modify to take stack size as input
 */
int main(int argc, char** argv) {
    struct stack s;
    init_stack(&s);
    int inputs[] = { 5, 11, 7, 231, 4, 19, 32, 65, 44, 41, 9, 77 };
    int sz = sizeof(inputs)/sizeof(int);
    int i;
    for (i = 0; i < sz; i++) {
        push(&s, inputs[i]);
        print(s);
    }
    while (!empty(s)) {
        printf("popped: %d\n", pop(&s));
        print(s);
    }
}

