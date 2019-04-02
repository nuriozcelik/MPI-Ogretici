#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  const int buffer_count = 5000;
  float buffer[buffer_count];
  memset(buffer, 0, sizeof(buffer));//bufferin buffer boyutu kadar kısmı sıfır degeri ile set ediliyor.
  
  // 5000 elemanlı dizinin her elemanına 1000 defa rastgele değerler toplanarak ekleniyor
  for (int rep=0; rep < 1000; ++rep) {
    for (int i=0; i < buffer_count; ++i) {
      float val = (float)rand() / RAND_MAX;
      buffer[i] += val;
    }
  }

  // reception adlı değişken ve buffer değişkeni Reduce fonksiyonuna gönderilerek toplama işlemi gerçekleştiriliyor.
    float reception[buffer_count];
    MPI_Reduce(&buffer, &reception, buffer_count, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);


  // sonuçlar yazdırılıyor
  if (rank == 0) {
    for (int i=0; i < buffer_count; ++i)
      std::cout << i <<":  "<< reception[i] << std::endl;
  }
  

  MPI_Finalize();
  
  return 0;
}