/*
 * El programa se debe compilar incluyendo la bandera -lm
 * gcc -o r.out regresion.c -lm
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para time_t

#include "../lib/server_functions.h"

point regresion(int size) {
  time_t t;
  srand((unsigned)time(&t)); // Hacer random real

  int *arr = (int *)malloc(sizeof(int) * size);

  double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumXX = 0.0;
  // Generar n numeros random

  for (int i = 0; i < size; i++) {
    arr[i] = rand() % 10;
    printf("%d ", arr[i]);

    // Para regresion lineal
    // La posicion del arreglo es la x, arr[i] la y.
    sumX += i;
    sumY += arr[i];
    sumXX += pow(i, 2.0);
    sumXY += (i * arr[i]);
  }

  double avgX = sumX / (double)size;
  double avgY = sumY / (double)size;

  // Hacer regresion lineal
  point p;
  p.b1 = (sumXY - (size * avgX * avgY)) / (sumXX - (size * pow(avgX, 2.0)));
  p.b0 = avgY - p.b1 * avgX;

  free(arr);

  return p;
}
