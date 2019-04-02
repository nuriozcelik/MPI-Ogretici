///////////////////////////////////////////////////////////
//        collective_communication_bcast.cpp             //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int buffer[5];

  if (rank==0) {
    // buffer a veri atilir
    for (int i=0; i < 5; ++i)
      buffer[i] = i*i;
  }

  //Tum islemlere buffer degeri gonderilir
  MPI_Bcast(buffer, 5, MPI_INT, 0, MPI_COMM_WORLD);

  //Tum islemlerin buffer degeri ekrana yazilir
  std::cout << "Process #" << rank << "; Buffer = (";
  for (int i=0; i < 5; ++i)
    std::cout << buffer[i] << (i < 4 ? " " : "");
  std::cout << ")" << std::endl;
  
  MPI_Finalize();
}