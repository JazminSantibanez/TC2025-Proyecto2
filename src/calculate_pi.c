#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/server_functions.h"

#define NUM_THREADS 8

static long steps = 1000000000;
double step;

double calculate_pi() {
  double pi = 0.0;
  double sum[NUM_THREADS];

  step = 1.0 / (double)steps;
  omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
  {
    double x;
    int id, i;
    id = omp_get_thread_num();
    for (i = id, sum[id] = 0.0; i < steps; i = i + NUM_THREADS) {
      x = (i + 0.5) * step;
      sum[id] += 4.0 / (1.0 + x * x);
    }
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pi += sum[i] * step;
  }

  return pi;
}
