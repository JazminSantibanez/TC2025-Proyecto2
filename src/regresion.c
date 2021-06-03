#include <stdlib.h>
#include <stdio.h>
#include <time.h> //Para time_t

double*regresion(int);

double* regresion(int size)
{
    time_t t;
    srand((unsigned) time(&t)); //Hacer random real
    int *arr;
    double *ans;

    arr = (int *)malloc(sizeof(int) *size);
    ans = (double *)malloc(sizeof(double) * 2);

    //Generar n numeros random
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
    }

    //Hacer regresion lineal
    return ans;
}