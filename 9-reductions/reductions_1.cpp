#include <iostream>
#include <mpi.h>
#include <cmath>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // baslangic degerleri ataniyor, u_i = i^2; v_i = log(i+1)
  float u_i = rank*rank;
  float v_i = log(rank+1.0);

  // Ortalama deeger hesaplaniyor
  float tmp = u_i * v_i;

  // Process 0 icerisindeki buffera degerler toplaniyor
  float result;
  MPI_Reduce(&tmp, &result, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0) {
    std::cout << "Reduce fonsksiyonundaki toplam : " << result << std::endl;

    // sonuclar normal toplama yontemi ile kiyaslaniyor
    float validation = 0.0f;
    for (int i=0; i < size; ++i)
      validation += i*i * log(i+1.0f);

    std::cout << "Doğrulama değeri : " << validation << std::endl;
  }
  
  MPI_Finalize();
  
  return 0;
}