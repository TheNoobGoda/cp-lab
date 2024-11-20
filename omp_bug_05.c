#include <omp.h>
#include <stdio.h>

#define NTHREADS 4
#define N 20

void print_section(int, int, long *);

int main (int argc, char *argv[]) {
  int i, nthreads, tid, section;
  long a[N], b[N], c[N];

  for (i = 0; i < N; i++)
    a[i] = b[i] = i;

  #pragma omp parallel num_threads(NTHREADS) private(c,i,tid,section)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Number of threads: %d\n", nthreads);
    }
    #pragma omp barrier
    printf("Thread %d: starting\n", tid);
    #pragma omp barrier
    #pragma omp sections nowait
    {
      #pragma omp section
      {
        section = 1;
        for (i = 0; i < N; i++)
          c[i] = a[i] * b[i];
        print_section(section, tid, c);
      }
      #pragma omp section
      {
        section = 2;
        for (i = 0; i < N; i++)
          c[i] = a[i] + b[i];
        print_section(section, tid, c);
      }
    }
    #pragma omp barrier
    printf("Thread %d: finishing\n",tid);
  }
  return 0;
}


void print_section(int section, int tid, long *v) {
  int i, j;

  j = 1;
  #pragma omp critical  // synchronize printing
  {
    printf("Thread %d: start printing section %d\n", tid, section);
    for (i = 0; i < N; i++) {
      printf("%ld  ", v[i]);
      j++;
      if (j == 6) {
        printf("\n");
        j = 1;
      }
    }
  }

  // #pragma omp barrier  // wait until all sections are printed
  printf("Thread %d: end printing section %d\n", tid, section); 
  return;
}
