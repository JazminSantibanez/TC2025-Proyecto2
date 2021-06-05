/*
 * El programa se debe compilar incluyendo la bandera -fopenmp
 * gcc -o p.out Pthreads.c -fopenmp
 */

#include <omp.h> //Para OpenMP threads
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Para time_t

#include "../lib/server_functions.h"

#define NUM_THREADS 5

void print_matrix(int size, int mat[size][size]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf(" %i ", mat[i][j]);
    }
    printf("\n");
  }
}

int total_sum(int mat_size) {
  int matrix[mat_size][mat_size], total_sum = 0;

  time_t t;
  srand((unsigned)time(&t)); // Hacer random real

  // Inicializar matrices en valores al azar
  for (int i = 0; i < mat_size; i++) {
    for (int j = 0; j < mat_size; j++) {
      matrix[i][j] = rand() % 10;
    }
  }

  printf(" \nMatriz al azar de %dx%d: \n", mat_size, mat_size);
  print_matrix(mat_size, matrix);

  omp_set_num_threads(NUM_THREADS);

#pragma omp parallel for reduction(+ : total_sum)
  for (int i = 0; i < mat_size; i++) {
    for (int j = 0; j < mat_size; j++) {
      total_sum += matrix[i][j];
    }
  }

  return total_sum;
}
