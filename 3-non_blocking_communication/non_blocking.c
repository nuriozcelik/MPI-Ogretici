///////////////////////////////////////////////////////////
//                      non-blocking.c                   //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>


void play_non_blocking_scenario();
void play_blocking_scenario();
void print_buffer(int *buffer);

#define buffer_count 3

int buffer[buffer_count];
int rank, size;


int main(int arg, char** argv){

  //Mpi kutuphanesinin baslatilmasi
  MPI_Init(&arg, &argv);

  //Size ve Rank degerlerinin okunmasi
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //blocking uygulamanin gerceklestigi senaryo
  play_blocking_scenario();

  //non-blocking uygulamanin gerceklestigi senaryo
  play_non_blocking_scenario(); 

  //MPI sureci tamamlanir
  MPI_Finalize();

  return 0;
}

void play_non_blocking_scenario() {

  MPI_Request request;
  MPI_Status  status;

  //haberlesme durumunu tutacak bayraklar tanimlanir
  int request_finished = 0;
  int request_complete = 0;

  
  // Buffer baslatilir
  for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);

  //islemler ayni hizaya getirilir
  MPI_Barrier(MPI_COMM_WORLD);
  // kronometre baslatilir
  double time = -MPI_Wtime(); // zaman sayaci icin kullanılan bir fonksiyondur

  
  
  if (rank == 0) {
    sleep(3);

    // Process 1 e non-blocking gonderim islemi baslatilir, request degeri haberlesme takibi icin kullanilacaktir
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    
    double time_left = 6000.0;
    while (time_left > 0.0) {
      usleep(1000); // 1 ms calis

      // request in tamamlanip tamamlanmadigini kontrol et
      if (!request_complete) {
          MPI_Test(&request, &request_complete, &status);
      }
      
      
    
      time_left -= 1000.0;
    }

    // request hala tamamlanmadiysa tamamlanasiya kadar burada bekle
        if (!request_complete){
            MPI_Wait(&request, &status);
        }
    // bufferi ikinci adima hazirla
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = -i;

    //  process 1 icin farkli bir tag ile iletisim baslatilir
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
    time_left = 3000.0;
    while (time_left > 0.0) {
      usleep(1000); // 1ms calis

      // request in tamamlanip tamamlanmadigini kontrol et
        if (!request_complete) {
          MPI_Test(&request, &request_complete, &status);
      }
   
      time_left -= 1000.0;
    }
    // Tamamlanmasini bekle
    if (!request_complete){
            MPI_Wait(&request, &status);
        }
  }
  else {
    // 5 saniye bekle
    sleep(5);

    // Process 0 dan non-blocking alma islemini baslat 
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

    // request tamamlanasiya kadar burada bekle
    MPI_Wait(&request, &status);

    //alinan degeri ekrana bas
    print_buffer(buffer);
    
    // 3 sn için calis
    sleep(3);

    // Bir diger alma islemini baslat
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);

    // tamamlanmasini bekle
    MPI_Wait(&request, &status);
    print_buffer(buffer);
  }


  // Kronometreyi durdur
  time += MPI_Wtime();

  // Harcanan toplam zamani hesapla, reduce daha sonra ele alınacak
  double final_time;
  MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  
  if (rank == 0)
    printf("Non-Blocking Senaryo icin toplam zaman : %f s.\n",final_time);
}
void print_buffer(int *buffer){
    for(int i = 0; i < buffer_count; i++)
    {
        printf("Bufferda bulunan %d. deger  = %d\n", i, *((buffer)+i));
    }    
}
// Bu fonksiyon blocking iletisime ornek saglamak amaciyla yazilmistir.
void play_blocking_scenario() {

  // buffer degiskenini doldur
  for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);

  //Processler ayni hizaya getirilir
  MPI_Barrier(MPI_COMM_WORLD);

  // Kronometreyi baslatir
  double time = -MPI_Wtime(); // Bu komut zamani olcmemize yardım edecektir.

  // process 0 içinde kosacak olan kodlar
  if (rank == 0) {

    //3 sn islem yap(bekle)
    sleep(3);

    //process 1 e 0 tag'i ile buffer verisini gonder
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD);

    //6sn calis(bekle)
    sleep(6);
    
    // ikinci adim icin buffer guncellenir, 0, -1, -2 olarak
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = -i;
    
    //yeni buffer degeri process 1 e 1 etiketi ile gonderilir
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 1, MPI_COMM_WORLD);
  }
  else {
    //process 1 5 sn bekletilir.
    sleep(5);

    //process 0 dan 0 etiketine sahip mesaj alınarak buffer degerine atılır
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //alinan deger ekrana basilir
    print_buffer(buffer);

    //process 1 3 sn bekletilir
    sleep(3);

    //process 0 dan 1 etiketine sahip mesaj alinarak buffer degerine atilir
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    //buffer degeri ekrana yazilir
    print_buffer(buffer);
  }

  time += MPI_Wtime();
  
  // Bu satir biz her bir process de harcanan maksimum sureyi verecektir.
  // reduce islemi daha sonra islenecek
  double final_time;
  MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0)
    printf("Blocking Com. icin harcanan toplam zaman : %f s.\n",final_time);
}