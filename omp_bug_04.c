#include <omp.h>
#include <stdio.h>

#define NTHREADS 4
#define N 100

int main (int argc, char *argv[]) {
  int nthreads, tid, i, j;
  long a[N][N];

  #pragma omp parallel num_threads(NTHREADS) private(tid,i,j,a) shared(nthreads)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads: %d\n", nthreads);
    }
    #pragma omp barrier
    printf("Thread %d: starting\n", tid);
    #pragma omp barrier
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
        a[i][j] = tid + i + j;
    printf("Thread %d: a[%d][%d] = %ld\n", tid, N-1, N-1, a[N-1][N-1]);
    #pragma omp barrier
    printf("Thread %d: finishing\n", tid);
  }
  return 0;
}

