#ifndef BINARY_EXPRESSION_TREE_H
#define BINARY_EXPRESSION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node* left;
    struct Node* right;
} Node;

#endif // BINARY_EXPRESSION_TREE_H

