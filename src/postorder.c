#include "binaryExpressionTree.h"
#include "parseStrToTree.c"
#include "stringError.c"

/*
    This function prints the nodes of the binary expression in postorder traversal.

    Parameters:
    node - pointer to the root of the binary expression tree

    Return Values:
    N/A
*/
void printTree(Node *node)
{

    // Returns if node is null
    if (node == NULL)
    {
        return;
    }

    // Print left subtree
    if (node->left != NULL)
    {
        printTree(node->left);
    }

    // Print right subtree
    if (node->right != NULL)
    {
        printTree(node->right);
    }

    // Print current value
    printf(" %s ", node->value);

    return;
}

/*
    This function displays the expression in argv[1] in postorder traversal.

    Parameters:
    argc - number of command line arguments given
    argv - array of command line arguments

    Return Values:
    0
*/
int main(int argc, char *argv[])
{

    // Checks for sufficient number of arguments
    if (argc < 2)
    {
        fprintf(stderr, "Error: syntax error.\n");
        return 0;
    }

    // Checks for string error
    if (isStringError(argv[1]) == -1)
    {
        return 0;
    }

    // Attempts to parse string to tree
    Node *root = parseStrToTree(argv[1]);
    if (root != NULL)
    {
        printTree(root);
        printf("\n");
    }

    // Frees dynamically allocated memory
    freeTree(root);
    return 0;
}
