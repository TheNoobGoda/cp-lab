#include <omp.h>
#include <stdio.h>

#define NTHREADS 4
#define N 4000

int main (int argc, char *argv[]) {
  int i, tid;
  long total = 0;

  #pragma omp parallel num_threads(NTHREADS) private(tid) reduction(+: total)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      int nthreads = omp_get_num_threads();
      printf("Number of threads: %d\n", nthreads);
    }
    total = 0;
    #pragma omp for
    for (i = 0; i < N; i++)
      total = total + i;
  }
  printf("Total = %ld\n", total);
  return 0;
}
