///////////////////////////////////////////////////////////
//                   race_conditions.c                   //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
 

int main(int argc, char **argv) {

  //MPI baslatilir
  MPI_Init(&argc, &argv);
 
  //Non blocking iletisimde kullanilacak degiskenler
  MPI_Request request;
  MPI_Status  status;
  int request_complete = 0;
 
  //MPI da calisacak islemlerin rank ve size degerleri aliniyor
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  //iletisimde kullanilacak verinin boyutu
  const int buffer_count = 10;
  int buffer[buffer_count];
 
  // Rank 0 gönderir, rank 1 alır
  if (rank == 0) {
    // Buffer dolduruluyor
    printf("Process 0 gonderiyor : ");
    for (int i=0; i < buffer_count; ++i) {
      buffer[i] = i*i;
      printf("%d ", buffer[i]);
    }
    printf("\n");

    // Veri gonderiliyor ve 5sn bekleniyor
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    sleep(5);
  }
  else {
    // buffer sifirlaniyor
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = 0;

    // Alim gerceklesiyor ve 5sn bekleniyor
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    sleep(1);

    // process 1 tarafından alinan degerler yazdiriliyor
    int ite = 0;
      printf("Process 1 aldi : ");
      for (int i=0; i < buffer_count; ++i)
	  printf("%d ", buffer[i]);
      printf("\n");
  }
 
  MPI_Finalize();
}