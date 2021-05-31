#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_THREADS 50

int main(int argc, char *argv[])
{
    if (argc > 3)
    {
        printf(" !! Error: El programa acepta como máximo 1 argumento ");
        return EXIT_FAILURE;
    }
    else 
    {
        int numThreads = 0;

        if (argc == 2)
        {
            numThreads = atoi(argv[1]);
        } 
        else if (argc == 1)
        {
            numThreads = DEFAULT_THREADS;
        }
    }
    return EXIT_SUCCESS;
}