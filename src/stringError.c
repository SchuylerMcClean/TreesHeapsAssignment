#ifndef STRING_ERROR_C
#define STRING_ERROR_C

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
    This function checks for invalid characters in the input string.

    Parameters:
    str - pointer to the expression string

    Return Values:
    -1 - if invalid character found
    0 - if no invalid characters found
*/
int invalidChars(char *str)
{

    for (int i = 0; i < strlen(str); i++)
    {
        if (!(str[i] == '(' ||
              str[i] == ')' ||
              str[i] == '+' ||
              str[i] == '-' ||
              str[i] == '*' ||
              str[i] == '/' ||
              str[i] == 'x' ||
              str[i] == '.' ||
              (str[i] >= '0' &&
               str[i] <= '9')))
        {
            return -1; // Invalid character found, return -1
        }
    }
    return 0; // No invalid characters found, return 0
}

/*
    This function checks for bracket mismatches in the input string.

    Parameters:
    str - pointer to the expression string

    Return Values:
    -1 - if bracket mismatch found
    0 - if no bracket mismatch found
*/
int bracketMismatch(char *str)
{

    int openBrackets = 0;
    int closeBrackets = 0;

    // Iterates through the characters and counts open/closed brackets
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(')
        {
            openBrackets++;
        }
        else if (str[i] == ')')
        {
            closeBrackets++;
        }

        // If there are more closed brackets then open brackets at any point, return -1
        if (closeBrackets > openBrackets)
        {
            return -1;
        }
    }

    // At end of string, if number of open brackets not equal the number of closed brackets, return -1
    if ((openBrackets != closeBrackets) || (openBrackets == 0) || (closeBrackets == 0))
    {
        return -1;
    }
    return 0; // Bracket error not found, return 0
}

/*
    This function checks for errors in the input expression string.

    Parameters:
    str - pointer to the expression string

    Return Values:
    0 - if no errors found
    -1 - if errors found
*/
int isStringError(const char *str)
{

    // Dynamic allocation of str so that other functions have char* instead of const char*
    char *string = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(string, str);

    // Checks for invalid characters in string
    int invalid = invalidChars(string);
    if (invalid == -1)
    {
        fprintf(stderr, "Error: syntax error.\n");
        return -1;
    }

    // Checks for bracket mismatch
    int mismatch = bracketMismatch(string);
    if (mismatch == -1)
    {
        fprintf(stderr, "Error: syntax error.\n");
        return -1;
    }

    free(string);
    return 0; // No invalid characters or bracket mismatches
}

#endif // STRING_ERROR_C
