///////////////////////////////////////////////////////////
//                pobing_incoming_conditions.c           //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char **argv) {

  //MPI baslatiliyor
  MPI_Init(&argc, &argv);

  //MPI rank ve size degerleri
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    // Process 0 rastgele degerleri process 1 e integer olarak gonderiyor (10 ve 25 arasinda) 
    int n_items = rand() % 16 + 10; // Rastgele sayilar olusturuluyor fakat kotu bir yontem rastgele sayilar icin
    std::cout << "Process 0, rastgele gonderilecek bufer boyutu " << n_items << " int olacak." << std::endl;

    // Buffer baslatiliyor
    int *send_buf = new int[n_items];
    for (int i=0; i < n_items; ++i)
      send_buf[i] = i*i;

    std::cout << "Process 0, gonderiyor : ";
    for (int i=0; i < n_items; ++i)
      std::cout << send_buf[i] << " ";
    std::cout << std::endl;

    // Blocking gonderme
    MPI_Send(send_buf, n_items, MPI_INT, 1, 0, MPI_COMM_WORLD);

    // buffer siliniyor
    delete [] send_buf;
  }
  else {
    // alınan mesaja probing islemi uygulaniyor
    MPI_Status status;
    MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

    // probing yapilan mesajdan alinan status nesnesi vasitasiyla veri boyutu aliniyor
    int n_items;
    MPI_Get_count(&status, MPI_INT, &n_items);

    std::cout << "Process 1, probing sonucu alinan mesaj uzunlugu " << n_items << " int olacaktir." << std::endl;

    // Buffer degiskeni baslatiliyor, alinan degere gore
    int *recv_buf = new int[n_items];

    MPI_Recv(recv_buf, n_items, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Process 1, buffer aldi : ";
    for (int i=0; i < n_items; ++i)
      std::cout << recv_buf[i] << " ";
    std::cout << std::endl;

    delete [] recv_buf;
  }

  MPI_Finalize();
  
  return 0;
}