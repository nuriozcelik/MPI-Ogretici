///////////////////////////////////////////////////////////
//                    communication_modes.c              //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <iostream>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv) {

  //MPI baslatilir
  MPI_Init(&argc, &argv);

  //rank size degerleri elde edilir
  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // birisi buyuk birisi kucuk iki adet buffer olusturulur
  const int small_count = 50;
  const int big_count   = 100000;
  int buff1[small_count];
  int buff2[big_count];

  // Bekleme zamanı, farkın gönderilecek veri miktarından kaynaklandığını düşünüyorsanız, bu değerle oynayın
  const int waiting_time = 5; // saniye

  if (rank == 0) {
    // iki buffer da baslatilir
    for (int i=0; i < big_count; ++i) {
      if (i < small_count)
	buff1[i] = i;
      buff2[i] = i;
    }

    // 1.senkronizasyon
    MPI_Barrier(MPI_COMM_WORLD);

    // kronometre
    double time = -MPI_Wtime();

    // buffer standart modda gonderilir.
    MPI_Send(buff1, small_count, MPI_INT, 1, 0, MPI_COMM_WORLD);

    // Gonderme isleminin tamamlanma zamanini yazdirir
    std::cout << "Blocking 1 gonderme islemi icin harcanan zaman : " << time + MPI_Wtime() << "s" << std::endl;

    // 2. senkronizasyon
    MPI_Barrier(MPI_COMM_WORLD);
    time = -MPI_Wtime();

    // 2. buffer gonderilir
    MPI_Send(buff2, big_count, MPI_INT, 1, 1, MPI_COMM_WORLD);

    // zaman tekrar yazdirilir
    std::cout << "Blocking 2 gonderme islemi icin harcanan zaman : " << time + MPI_Wtime() << "s" << std::endl;
  }
  else {
    // senkronizasyon 1
    MPI_Barrier(MPI_COMM_WORLD);
    sleep(waiting_time);

    // c
    MPI_Recv(buff1, small_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "buffer 1 alindi" << std::endl;

    // senkronizasyon 2
    MPI_Barrier(MPI_COMM_WORLD);
    sleep(waiting_time);

    // alma bufferı 2
    MPI_Recv(buff2, big_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "buffer 2 alindi " << std::endl;
  }

  MPI_Finalize();
  
  return 0;
}