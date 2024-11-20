#include <omp.h>
#include <stdio.h>

#define NTHREADS 4
#define N 100

void mult(long*);
long a[N], b[N];

int main (int argc, char *argv[]) {
  int i;
  long total;

  for (i = 0; i < N; i++)
    a[i] = b[i] = i;
  total = 0;
  #pragma omp parallel num_threads(NTHREADS) shared(total)
  mult(&total);
  printf("Total = %ld\n", total);
  return 0;
}

void mult(long *total) {
  int i;

  #pragma omp master
  printf("Number of threads: %d\n", omp_get_num_threads());
  #pragma omp for reduction(+: (*total))
  for (i = 0; i < N; i++)
    *total += a[i] * b[i];
  return;
}
