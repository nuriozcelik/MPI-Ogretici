///////////////////////////////////////////////////////////
//         collective_communication_p2p.cpp             //
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
    // Buffera veri aktarilir
    for (int i=0; i < 5; ++i)
      buffer[i] = i*i;
    //tum islemere process 0 dan bu veri yayinlanir
    for (int id_dest=1; id_dest < size; ++id_dest)
      MPI_Send(buffer, 5, MPI_INT, id_dest, 0, MPI_COMM_WORLD);
  }
  else {
    //diger islemler bu veriyi alir
    MPI_Recv(buffer, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  //tum islemler buffer degerini ekrana yazar
  std::cout << "Process #" << rank << "; Buffer = (";
  for (int i=0; i < 5; ++i)
    std::cout << buffer[i] << (i < 4 ? " " : "");
  std::cout << ")" << std::endl;
  
  MPI_Finalize();
}