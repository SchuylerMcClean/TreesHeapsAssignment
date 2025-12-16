#include "binaryExpressionTree.h"
#include "parseStrToTree.c"
#include "stringError.c"
#include "calculateExpression.c"

/*
    This function calculates the expression in argv[1] with values from argv[2] if needed.

    Parameters:
    argc - number of command line arguments given
    argv - array of command line arguments

    Return Values:
    0
*/
int main(int argc, char *argv[])
{

    // Ensure correct number of arguments
    if (argc < 2)
    {
        fprintf(stderr, "Error: syntax error.\n");
        return 0;
    }

    // Check for errors in the expression string
    if (isStringError(argv[1]) == -1)
    {
        return 0;
    }

    // Parse the expression string into a binary expression tree
    Node *root = parseStrToTree(argv[1]);
    if (root == NULL)
    {
        return 0;
    }

    // Build variable list
    List *varList = NULL;

    // If variable values are provided, check that variable string is valid
    // and build the variable list
    if (argc == 3)
    {
        int isValidVariables = validateVariableString(argv[2]);
        if (isValidVariables == -1)
        {
            fprintf(stderr, "Error: syntax error in variable string.\n");
            return 0;
        }
        varList = buildVarList(argv[2]);
    }

    // Calculate the expression
    float *answer = calculateExpression(root, varList);

    // Print the result if no errors occurred
    if (answer != NULL)
    {
        printf("%4.2f\n", *answer);
    }

    // Free allocated memory
    freeTree(root);
    freeVarList(varList);

    return 0;
}
