#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int N, *v;

int prime(int x, int y) {
  if (y == 1) return 1;
  else if (x % y == 0) return 0;
  else return prime(x, y - 1);
}

int is_prime(int n) {
  if (n < 2) return 0;
  else return prime(n, n-1);
}

void load_vector() {
  int i;

  N = 32000;
  v = (int *) malloc(N * sizeof(int));
  for (i = 0; i < N; i++)
    v[i] = i;
  return;
}

int main(int argc, char **argv) {
    int numprocs, rank, i, init, finish;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);
    init = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    finish =MPI_Wtime();
    printf("time: %d\n",finish-init);

    MPI_Finalize();
}
