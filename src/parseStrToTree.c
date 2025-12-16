#ifndef PARSE_STR_TO_TREE_H
#define PARSE_STR_TO_TREE_H

#include "binaryExpressionTree.h"

/*
    This function finds the index of the main operator in the expression string.

    Parameters:
    str - pointer to the expression string

    Return Values:
    index - index of the main operator in the string
    -1 - if no operator found at the main level
*/
int findBiggestOperator(char *str)
{

    int openBrackets = 0;

    // Counts open/closed brackets and gets binary operator when only one set of brackets is open
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(')
        {
            openBrackets++;
        }
        else if (str[i] == ')')
        {
            openBrackets--;
        }
        // Gets binary operator when only one set of brackets is currently open
        else if ((openBrackets == 1) && (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'))
        {
            return i;
        }
    }
    return -1;
}

/*
    This function checks if a term is valid (either a variable 'xN' or a constant 'Y.YY').

    Parameters:
    str - pointer to the term string

    Return Values:
    0 - for valid term
    -1 - for invalid term
*/
int isValidTerm(char *str)
{

    // Ensures length-2 terms are valid 'xN' terms
    if (strlen(str) == 2)
    {
        if ((str[0] == 'x') && (str[1] >= '1' && str[1] <= '9'))
        {
            return 0; // Valid
        }
        return -1; // Invalid
    }
    // Ensures length-4 terms are valid 'Y.YY' terms
    else if (strlen(str) == 4)
    {
        if ((str[0] >= '0' && str[0] <= '9') &&
            (str[1] == '.') &&
            (str[2] >= '0' && str[2] <= '9') &&
            (str[3] >= '0' && str[3] <= '9'))
        {
            return 0; // Valid
        }
        return -1;
    }
    // Length not 2 or 4 is invalid
    return -1;
}

/*
    This function frees the memory allocated for the binary expression tree.

    Parameters:
    root - pointer to the root of the binary expression tree

    Return Values:
    N/A
*/
void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root->value);
    free(root);
}

/*
    This function builds a binary expression tree from the input string.

    Parameters:
    str - pointer to the expression string

    Return Values:
    Node pointer - pointer to the root of the binary expression tree
*/
Node *buildTree(char *str)
{

    Node *newNode = malloc(sizeof(struct Node));
    int indexBigOperator = findBiggestOperator(str);

    // If no operator in biggest set of brackets is found, must be a term
    if (indexBigOperator == -1)
    {
        // Checks if term is valid
        if (isValidTerm(str) == -1)
        {
            fprintf(stderr, "Error: syntax error.\n");
            free(newNode);
            return NULL;
        }
        // If valid term, creates node
        newNode->value = malloc(sizeof((strlen(str) + 1) * sizeof(char) + 1));
        strcpy(newNode->value, str);
        newNode->left = NULL;
        newNode->right = NULL;
    }
    // If operator is found
    else
    {
        char *str1 = malloc((strlen(str) + 1) * sizeof(char) + 1);
        strcpy(str1, str);
        char *str2 = malloc((strlen(str) + 1) * sizeof(char) + 1);
        strcpy(str2, str);

        // Partition of string to save only the operator into the node
        str1[indexBigOperator + 1] = '\0';
        newNode->value = malloc(sizeof(char) + 1);
        strcpy(newNode->value, &str1[indexBigOperator]);

        // Partition of string from first bracket up to ooperator
        str2[indexBigOperator] = '\0';
        newNode->left = buildTree(str2 + 1);

        // If error in left subtree, return null
        if (newNode->left == NULL)
        {
            free(str1);
            free(str2);
            freeTree(newNode);
            return NULL;
        }

        // Partition of string from operator to end of string
        str2[strlen(str) - 1] = '\0';
        newNode->right = buildTree(str2 + indexBigOperator + 1);

        // If error in right subtree, return null
        if (newNode->right == NULL)
        {
            free(str1);
            free(str2);
            freeTree(newNode);
            return NULL;
        }

        // Free dynamically allocated data
        free(str1);
        free(str2);
    }
    return newNode;
}

/*
    This function parses the input expression string into a binary expression tree.

    Parameters:
    str - pointer to the expression string

    Return Values:
    Node pointer - pointer to the root of the binary expression tree
*/
Node *parseStrToTree(const char *str)
{

    char *string = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(string, str);

    // Build tree
    Node *root = buildTree(string);

    free(string);
    return root;
}
#endif // PARSE_STR_TO_TREE_H
