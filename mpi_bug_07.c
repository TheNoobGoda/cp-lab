#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define REQS 1000
#define DISP 100

int main(int argc, char *argv[]) {
  int numprocs, rank, tag, src, dest, num, offset, i;
  MPI_Request reqs[REQS];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 if (numprocs != 2) {
    MPI_Finalize();
    if (rank == 0)
      printf("Run the program with 2 processes!\n");
    exit(0);
  }

  printf("Proc %d starting...\n", rank);
  MPI_Barrier(MPI_COMM_WORLD);
  tag = 0;
  if (rank == 0) {
    dest = 1;
    num = 1;
    for (i = 1; i <= REQS; i++) {
      MPI_Send(&num, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
      if (i % DISP == 0)
	printf("Proc %d has done %d sends\n", rank, i);
    }
  } else {
    src = 0;
    offset = 0;
    for (i = 1; i <= REQS; i++) {
      MPI_Irecv(&num, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &reqs[offset]);
      offset += 1;
      if (i % DISP == 0)
	printf("Proc %d has done %d irecvs\n", rank, i);
    }
  } 
  if (rank == 1){
    MPI_Waitall(REQS, reqs, MPI_STATUS_IGNORE);
  }
  

  MPI_Finalize();
}
