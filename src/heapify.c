#include <stdio.h>
#include <stdlib.h>

typedef struct Object
{
    int key;
    int info[10];
} Object;

/*
    This function reads data values from the file "f.dat" and inserts them into a 2D array

    Parameters:
    fileName - the name of the file
    dataArray[][] - the 2D array with the data values

    Return Values:
    0 - if file is read successfully
    -1 - if file is not read successfully
*/
int readFile(char *fileName, int dataArray[20][10])
{

    int numOfInts = 0;
    FILE *fData = fopen(fileName, "r");

    // File opening failed, return -1
    if (fData == NULL)
    {
        fprintf(stderr, "Error: file cannot be opened.\n");
        return -1;
    }

    // Scan values until dataArray is populated, break if end of file is reached
    int endOfFile = 0;
    for (int i = 0; i < 20 && !endOfFile; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (fscanf(fData, "%02d ", &dataArray[i][j]) == 1)
            {
                numOfInts++;
            }
            else
            {
                endOfFile = 1;
                break;
            }
        }
    }
    // If end of file not yet reached, or less than 200 integers are in file, return -1
    if ((!feof(fData)) || (numOfInts != 200))
    {
        fclose(fData);
        fprintf(stderr, "Error: number of values not 200.\n");
        return -1;
    }
    fclose(fData);
    return 0;
}

/*
    This function creates the object array that contains the nodes of the heap

    Parameters:
    objArray[] - a pointer to the object array containing the nodes of the heap
    dataArray[][] - a 2D array containing the data values from the file

    Return Values:
    N/A
*/
void createObjectArray(Object *objArray[20], int dataArray[20][10])
{

    for (int i = 0; i < 20; i++)
    {

        // New object for each row
        Object *newObject = malloc(sizeof(Object));
        objArray[i] = newObject;

        // key = sum of first 3 values
        newObject->key = dataArray[i][0] + dataArray[i][1] + dataArray[i][2];

        for (int j = 0; j < 10; j++)
        {
            newObject->info[j] = dataArray[i][j];
        }
    }
}
/*
    This function achieves a max heap using a downheap algorithm.

    Parameters:
    objArray[] - a pointer to an object array with each node of the heap
    i - the value of the current parent node for downheap

    Return Values:
    N/A
*/
void heapify(Object *objArray[20], int i)
{
    int biggest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    // Check that left child exists then check if it's bigger than parent
    if ((leftChild < 20) && (objArray[leftChild]->key > objArray[biggest]->key))
    {
        biggest = leftChild;
    }
    // Check that right child exists then check if it's bigger than parent
    if ((rightChild < 20) && (objArray[rightChild]->key > objArray[biggest]->key))
    {
        biggest = rightChild;
    }

    // Swap if a child is larger than the parent
    if (biggest != i)
    {
        Object *temp = objArray[i];
        objArray[i] = objArray[biggest];
        objArray[biggest] = temp;

        // Continue downheap
        heapify(objArray, biggest);
    }
}

/*
    This function frees the heap object nodes from the object array

    Parameters:
    objArray[] - object array of heap nodes

    Return Values:
    N/A
*/
void freeHeap(Object *objArray[20])
{
    for (int i = 0; i < 20; i++)
    {
        free(objArray[i]);
    }
}

/*
    This function displays values of a max heap.

    Parameters:
    objArray[] - the object array containing the nodes of the max heap

    Return Values:
    N/A
*/
void printNodes(Object *objArray[20])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%02d ", objArray[i]->info[j]);
        }
        printf("\n");
    }
}
