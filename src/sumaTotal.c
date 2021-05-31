/*
 * El programa se debe compilar incluyendo la bandera -fopenmp
 * gcc -o p.out Pthreads.c -fopenmp
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Para time_t
#include <omp.h> //Para OpenMP threads


//Header de funciones
int sumaTotal(int num);

int sumaTotal(int matSize)
{
    time_t t;
    srand((unsigned) time(&t)); //Hacer random real
    int matrix[matSize][matSize];

    //Inicializar matrices en valores al azar
    for(int i=0; i<matSize; i++)
    {
        for(int j=0; j<matSize; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
    
}