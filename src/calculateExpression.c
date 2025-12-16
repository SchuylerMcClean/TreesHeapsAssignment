// ifndef and define not necessary here, added for consistency with other files
#ifndef CALCULATE_EXPRESSION_C
#define CALCULATE_EXPRESSION_C

#include "binaryExpressionTree.h"

typedef struct List
{
    int variableIndex;
    float *value;
    struct List *next;
} List;

/*
    This function frees the memory allocated for the variable linked list.

    Parameters:
    varList - pointer to the head of the variable linked list

    Return Values:
    N/A
*/
void freeVarList(List *varList)
{
    List *curNode = varList;
    List *nextNode;

    while (curNode != NULL)
    {
        nextNode = curNode->next;
        free(curNode->value);
        free(curNode);
        curNode = nextNode;
    }
}

/*
    This function validates the variable assignment string.

    Parameters:
    str - pointer to the variable string

    Return Values:
    0 - for valid variable string
    -1 - for invalid variable string
*/
int validateVariableString(const char *str)
{

    // Returns if variable string is invalid length
    if (strlen(str) % 8 != 7)
    {
        return -1;
    }

    for (int i = 0; i < strlen(str); i = i + 8)
    {
        // Missing 'x'
        if (!(str[i] == 'x'))
        {
            return -1;
        }
        // Invalid variable index
        if (!(str[i + 1] >= '1' && str[i + 1] <= '9'))
        {
            return -1;
        }
        // Missing '='
        if (str[i + 2] != '=')
        {
            return -1;
        }
        // Invalid digit
        if (!(str[i + 3] >= '0' && str[i + 3] <= '9'))
        {
            return -1;
        }
        // Missing decimal point
        if (str[i + 4] != '.')
        {
            return -1;
        }
        // Invalid digit
        if (!(str[i + 5] >= '0' && str[i + 5] <= '9'))
        {
            return -1;
        }
        // Invalid digit
        if (!(str[i + 6] >= '0' && str[i + 6] <= '9'))
        {
            return -1;
        }
        // Missing semicolon
        if (!((i + 7 == strlen(str)) || (str[i + 7] == ';')))
        {
            return -1;
        }
    }
    // Valid variable string
    return 0;
}

/*
    This function builds a linked list of variable assignments from the input variable string.

    Parameters:
    str - pointer to the variable string

    Return Values:
    head - pointer to the head of the variable linked list
*/
List *buildVarList(const char *str)
{

    List *head = NULL;
    List *tail = head;

    for (int i = 0; i < strlen(str); i = i + 8)
    {

        // Null-terminate at semicolon (end of float value)
        char *string = malloc(sizeof(char) * (strlen(str) + 1));
        strcpy(string, str);
        string[i + 7] = '\0';

        // Malloc new list node and float value
        List *newNode = malloc(sizeof(struct List));

        // Append node to linked list
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        // Convert char to int
        newNode->variableIndex = str[i + 1] - '0';

        newNode->value = (float *)malloc(sizeof(float));
        // Convert substring to float
        *(newNode->value) = atof(string + i + 3);

        newNode->next = NULL;
        free(string);
    }
    return head;
}

/*
    This function retrieves the value of a variable from the variable linked list.

    Parameters:
    index - index of the variable to retrieve
    varList - pointer to the head of the variable linked list

    Return Values:
    float pointer - pointer to the float value of the variable if found
    NULL - if variable is not found or list is empty
*/
float *getVarValue(int index, List *varList)
{

    // Variable list is empty
    if (varList == NULL)
    {
        return NULL;
    }

    // Checks to find variable index
    List *curNode = varList;
    while (curNode != NULL)
    {
        if (curNode->variableIndex == index)
        {
            return curNode->value;
        }
        curNode = curNode->next;
    }
    // Variable not found
    return NULL;
}

/*
    This function calculates the value of the expression represented by the binary expression tree.

    Parameters:
    node - pointer to the root node of the binary expression tree
    varList - pointer to the head of the variable linked list

    Return Values:
    float pointer - pointer to the float value of the expression if successful
    NULL - if an error occurs (e.g., undefined variable, division by zero)
*/
float *calculateExpression(Node *node, List *varList)
{

    // All float values are returned as pointers to floats to allow for NULL returns when errors occur

    if (node == NULL)
    {
        return NULL;
    }

    // Leaf node (variable or constant)
    if ((node->left == NULL) && (node->right == NULL))
    {

        // Variable node in the form 'xN'
        if (node->value[0] == 'x')
        {

            // Get variable index N from 'xN'
            int varIndex = node->value[1] - '0';

            // Get variable value from variable list
            float *varValue = getVarValue(varIndex, varList);

            // If varValue is NULL, variable not found in variable list or list is empty
            if (varValue == NULL)
            {
                fprintf(stderr, "Error: undefined argument.\n");
                return NULL;
            }
            return varValue;
        }

        // Constant node, therefore convert string from binary tree node to float
        else
        {
            float *constValue = malloc(sizeof(float));
            *constValue = atof(node->value);
            return constValue;
        }
    }

    float *leftValue;
    float *rightValue;

    // Returns null if left or right subtrees are null
    leftValue = calculateExpression(node->left, varList);
    if (leftValue == NULL)
    {
        return NULL;
    }
    rightValue = calculateExpression(node->right, varList);
    if (rightValue == NULL)
    {
        return NULL;
    }

    // Perform operation based on operator in the current node
    float *result = malloc(sizeof(float));

    // Addition
    if (strcmp(node->value, "+") == 0)
    {
        *result = *leftValue + *rightValue;
        return result;
    }

    // Subtraction
    else if (strcmp(node->value, "-") == 0)
    {
        *result = *leftValue - *rightValue;
        return result;
    }

    // Multiplication
    else if (strcmp(node->value, "*") == 0)
    {
        *result = *leftValue * *rightValue;
        return result;
    }

    // Division
    else if (strcmp(node->value, "/") == 0)
    {
        // Division by zero error check
        if (*rightValue == 0.00f)
        {
            fprintf(stderr, "Error: division by zero.\n");
            return NULL;
        }
        *result = *leftValue / *rightValue;
        return result;
    }
    // Should not reach here
    return NULL;
}
#endif // CALCULATE_EXPRESSION_C
