#include <stdlib.h>
#include <stdio.h>

struct node {
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
};

struct tree {
    struct node* root;
};

/*
 * Pointers to functions to switch between
 * recursive and iterative implementations
 */
struct node* (*smallest)(struct node* n);
struct node* (*largest)(struct node* n); 
struct node* (*find)(struct node*, int key);
void (*inorder)(struct node* n);
void (*reverse_order)(struct node* n); 

static struct node* make_node(int key) {
    struct node** ppnode;
    struct node* pnode;

    // allocate memory for the pointer to the
    // node on the heap
    ppnode = malloc(sizeof(struct node*));
    if (NULL == ppnode) {
        perror("Unable to allocate memory for ppnode");
        exit(-1);
    }
    // allocate memory for the node on the heap
    pnode = malloc(sizeof(struct node));
    if (NULL == pnode) {
        perror("Unable to allocate memory for pnode");
        exit(-1);
    }

    pnode->key = key;

    // note that we can't just return the address
    // of pnode because it's allocated on the
    // stack and will be inaccessible once this
    // function returns
    *ppnode = pnode;
    return *ppnode;
}

static void insert(struct tree* t, struct node* n) {
    if (NULL == t->root) {
        t->root = n;
        return;
    }
    struct node* temp = t->root;
    while (NULL != temp) {
        if (n->key <= temp->key) {
            if (NULL == temp->left) {
                temp->left = n;
                n->parent = temp;
                break;
            } else {
                temp = temp->left;
            }
        } else {
            if (NULL == temp->right) {
                temp->right = n;
                n->parent = temp;
                break;
            } else {
                temp = temp->right;
            }
        }
    }
}

/*
 * Replace the subtree rooted at node u
 * with the subtree rooted at node v
 */
static void transplant(struct tree* t, struct node* u, struct node* v) {
    // u is the root node
    if (NULL == u->parent) {
        t->root = v;
    // u is the left child
    } else if (u == u->parent->left) {
        u->parent->left = v;
    // u is the right child
    } else {
        u->parent->right = v;
    }
    if (NULL != v) {
        u->parent = v->parent;
    }
}

static void delete(struct tree* t, struct node* z) {
    // z has no left child, replace z with its right child
    if (NULL == z->left) {
        transplant(t, z, z->right);
    // z has no right child, replace z with its left child
    } else if (NULL == z->right) {
        transplant(t, z, z->left);
    } else { // z has both left and right children
        // find the successor of z
        struct node* y = smallest(z->right);
        // y is not an immediate child of z
        if (y->parent != z) {
            // replace y with its right child
            // note that y does not have a left child
            // because y is the successor of z
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        // replace z with y
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
}

static void print_node(struct node* n) {
    if (NULL == n) {
        return;
    }
    printf("%d\n", n->key);
}

static struct node* next(struct node* n) {
    if (NULL == n) {
        return NULL;
    } 
    if (NULL != n->right) {
        return smallest(n->right);
    } else {
        struct node* p = n;
        struct node* pp = n->parent;
        while (NULL != pp && pp->left == p) {
            p = pp;
            pp = p->parent;
        }
        return pp;
    }
}

static struct node* prev(struct node* n) {
    if (NULL == n) {
        return NULL;
    }
    if (NULL != n->left) {
        return largest(n->left);
    } else {
        return n;
    }
}

static struct node* recursive_smallest(struct node* n) {
    if (NULL == n) {
        return NULL;
    } 
    if (NULL == n->left) {
        return n;
    } else {
        recursive_smallest(n->left);
    }
}

static struct node* iterative_smallest(struct node* n) {
    if (NULL == n) {
        return NULL;
    }
    struct node* temp = n;
    while (NULL != temp->left) {
        temp = temp->left;
    }
    return temp;
}

static struct node* recursive_largest(struct node* n) {
    if (NULL == n) {
        return NULL;
    }
    if (NULL == n->right) {
        return n;
    } else {
        return recursive_largest(n->right);
    }
}

static struct node* iterative_largest(struct node* n) {
    if (NULL == n) {
        return NULL;
    }
    struct node* temp = n;
    while (NULL != temp->right) {
        temp = temp->right;
    }
    return temp;
}

static void recursive_inorder(struct node* n) {
    if (NULL == n) {
        return;
    }
    recursive_inorder(n->left);
    print_node(n);
    recursive_inorder(n->right);
}

static void iterative_inorder(struct node* n) {
    struct node* p = smallest(n);
    while (NULL != p) {
        print_node(p);
        p = next(p);
    }
}

static void recursive_reverse_order(struct node* n) {
    if (NULL == n) {
        return;
    }
    recursive_reverse_order(n->right);
    print_node(n);
    recursive_reverse_order(n->left);
}

static void iterative_reverse_order(struct node* n) {
    struct node* p = largest(n);
    while (NULL != p) {
        print_node(p);
        p = prev(p);
    }
}

static struct node* recursive_find(struct node* n, int key) {
    if (NULL == n) {
        return NULL;
    }
    if (key == n->key) {
        return n;
    } else if (key < n->key) {
        return recursive_find(n->left, key);
    } else {
        return recursive_find(n->right, key);
    }
}

static struct node* iterative_find(struct node* n, int key) {
    struct node* t = n;
    while (t != NULL) {
        if (key == t->key) {
            return t;
        } else if (key < t->key) {
            t = t->left;
        } else {
            t = t->right;
        }
    }
    return t;
}

int main(int argc, char** argv) {
    int input[] = { 34, 11, 17, 21, 8, 53, 3, 111, 30 };
    int sz = 9;

    struct tree t = { NULL };
    struct node* n;
    for (int i = 0; i < sz; i++) {
       n = make_node(input[i]);
       insert(&t, n);
    }

    // Switch between iterative and recursive
    smallest = recursive_smallest;
    largest = recursive_largest;
    find = recursive_find;
    inorder = recursive_inorder;
    reverse_order = recursive_reverse_order;


    inorder(t.root);

    struct node* z;
    
    //z = find(t.root, 111);
    //delete(&t, z);
    //printf("----\n");
    //inorder(t.root);

    //z = find(t.root, 3);
    //delete(&t, z);
    //printf("----\n");
    //inorder(t.root);

    z = find(t.root, 17);
    delete(&t, z);
    printf("----\n");
    inorder(t.root);
}


