/*
 * El programa se debe compilar incluyendo la bandera -fopenmp
 * gcc -o p.out Pthreads.c -fopenmp
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Para time_t
#include <omp.h> //Para OpenMP threads

#define NUM_THREADS 5

//Header de funciones
int sumaTotal(int num);
void printMatrix(int size, int mat[size][size]);

int sumaTotal(int matSize)
{
    int matrix[matSize][matSize], sumaTotal = 0;

    time_t t;
    srand((unsigned) time(&t)); //Hacer random real

    //Inicializar matrices en valores al azar
    for(int i=0; i<matSize; i++)
    {
        for(int j=0; j<matSize; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }

    printf(" \nMatriz al azar de %dx%d: \n", matSize, matSize);
    printMatrix(matSize, matrix);

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel for reduction(+:sumaTotal)
    for (int i = 0; i < matSize; i++)
    {
        for (int j = 0; j< matSize; j++)
        {
            sumaTotal += matrix[i][j];
        }
    }

    return sumaTotal;
}


void printMatrix( int size, int mat[size][size] )
{
    for (int i = 0; i < size; i++)
    {
        for (int j=0; j< size; j++)
        {
            printf(" %i ", mat[i][j]);
        }
        printf("\n");
    }
}