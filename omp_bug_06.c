#include <omp.h>
#include <stdio.h>

#define NTHREADS 4
#define N 1000000
#define PI 3.1415926535
#define DELTA .01415926535

int main (int argc, char *argv[]) {
  int nthreads, tid, i;
  float a[N], b[N];
  omp_lock_t locka, lockb;

  omp_init_lock(&locka);
  omp_init_lock(&lockb);
  #pragma omp parallel num_threads(NTHREADS) private(tid,i) shared(nthreads,a,b,locka,lockb) 
  {
    tid = omp_get_thread_num();
    #pragma omp master
    {
      nthreads = omp_get_num_threads();
      printf("Number of threads: %d\n", nthreads);
      omp_set_lock(&locka);
      omp_set_lock(&lockb);
    }
    #pragma omp barrier
    printf("Thread %d: starting\n", tid);
    #pragma omp barrier
    #pragma omp sections nowait
    {
      #pragma omp section
      {
        printf("Thread %d: initializing a[]\n",tid);
        for (i = 0; i < N; i++)
          a[i] = i;
        omp_unset_lock(&locka);
        omp_set_lock(&lockb);
        printf("Thread %d: updating b[]\n",tid);
        for (i = 0; i < N; i += 2)
          b[i] *= PI;
        omp_unset_lock(&lockb);
      }
      #pragma omp section
      {
        printf("Thread %d: initializing b[]\n",tid);
        for (i = 0; i < N; i++)
          b[i] = i;
        omp_unset_lock(&lockb);
        omp_set_lock(&locka);
        printf("Thread %d: updating a[]\n",tid);
        for (i = 1; i < N; i += 2)
          a[i] *= DELTA;
        omp_unset_lock(&locka);
      }
    }
    #pragma omp barrier
    printf("Thread %d: finishing\n", tid);
  }
  omp_destroy_lock(&locka);
  omp_destroy_lock(&lockb);
  return 0;
}
