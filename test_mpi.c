#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {

  int number;

  MPI_Init(NULL, NULL);      // initialize MPI environment
  int world_size; // number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank; // the rank of the process
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  
  char processor_name[MPI_MAX_PROCESSOR_NAME]; // gets the name of the processor
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);
  
  printf("Hello world from processor %s, rank %d out of %d processors. Name len: %d\n", processor_name, world_rank, world_size, name_len);

  
  if (world_rank == 0) {

    number = 42;
	  
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    fprintf(stderr,"Process 0 sent number %d to process 1.\n", number);
  }
  
  else {
    
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    fprintf(stderr,"Process 1 received number %d from process 0.\n", number);
  }
  
  
  MPI_Finalize(); // finish MPI environment
}
