///////////////////////////////////////////////////////////
//                      broadcast.cpp                    //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <iostream>
#include <iomanip>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // process 0 için girdi okunur
  int n_elements;
  double *buffer;
  if (rank == 0) {
    std::cout << "buffer eleman adeti gir"<< std::endl;
    std::cin >> n_elements;
    buffer = new double[n_elements];
    
    for (int i=0; i < n_elements; ++i){
      std::cout << "buffer eleman gir"<<std::endl;
      std::cin >> buffer[i];
    }
  }

  // n_elements degeri tum islemlere Broadcast edilir
  MPI_Bcast(&n_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);


  // process sifir disinde n_elements boyutlu buffer olusturulur
  if (rank != 0)
    buffer = new double[n_elements];

  // Buffer degeri her process e Broadcast edilir
  MPI_Bcast(buffer, n_elements, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  

  // rank a bagli toplam hesaplanir, process 1 toplami hesaplar
  double sum = 0.0;
  if(rank == 1){
      for(int i = 0; i < n_elements; i++)
      {
          sum += buffer[i];
      }
  }
  
  //process 0 negatif degerleri toplar
  if(rank == 0){
      for(int i = 0; i < n_elements; i++)
      {
          (buffer[i] < 0) ? sum += buffer[i] : sum +=0;
      }
      
  }

  
  std::cout << std::setprecision(16) << sum << std::endl;
  
  MPI_Finalize();
  delete [] buffer;

  return 0;
}