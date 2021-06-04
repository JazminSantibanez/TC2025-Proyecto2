#pragma once

typedef struct {
  double b0, b1;
} point;

double calculate_pi();
char *get_html();
int nearest_prime(int n);
point regresion(int size);
int total_sum(int num);
void print_matrix(int size, int mat[size][size]);
