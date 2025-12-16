#include "heapify.c"

/*
    This function reads data from a file and executes a max heap downheap algorithm with the values.

    Parameters:
    N/A

    Return Values:
    0
*/
int main()
{
    int dataArray[20][10];

    // If file read is successful, create object array, heapify it, and print the nodes
    if (readFile("f.dat", dataArray) == 0)
    {

        // Create object array
        Object *objArray[20];
        createObjectArray(objArray, dataArray);

        // Heapify to max heap
        for (int i = ((20 / 2) - 1); i >= 0; i--)
        {
            heapify(objArray, i);
        }

        // Print nodes
        printNodes(objArray);

        // Free dynamically allocated memory
        freeHeap(objArray);
    }
    return 0;
}
