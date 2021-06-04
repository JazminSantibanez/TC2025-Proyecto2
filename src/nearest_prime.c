#include <math.h>

#include "../lib/server_functions.h"

int nearest_prime(int n) {

  if (n & 1)
    n -= 2;
  else
    n--;

  int i, j;
  for (i = n; i >= 2; i -= 2) {
    if (i % 2 == 0)
      continue;
    for (j = 3; j <= sqrt(i); j += 2) {
      if (i % j == 0)
        break;
    }
    if (j > sqrt(i))
      return i;
  }

  return 2;
}
