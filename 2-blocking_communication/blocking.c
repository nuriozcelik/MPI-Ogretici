///////////////////////////////////////////////////////////
//                      blocking.c                       //
///////////////////////////////////////////////////////////

//kutuphaneler
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int arg, char** argv){

    //Mpi kutuphanesinin baslatilmasi
    MPI_Init(&arg, &argv);
    //Size ve Rank degerlerinin okunmasi
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Islemin yerel degerini oku
    //local_value process 0 icin farkli, process 1 icin farkli int deger tutacak
    int local_value;
    local_value = atoi(argv[1]);

    int other_value;

    //rank id si 0 olan islem bu if blogunda gerceklesecek
    if(rank == 0){
        //ilk islem icin gerekli kodlar burada gerceklesecektir.
        printf("process 0 gerceklesiyor\n");
        //process 1 e process 0 dan deger gonderilecek
        MPI_Send(&local_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        //process 1 den process 0 a veri aktarılacak
        MPI_Recv(&other_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        //2 degerin toplami ekrana yazılır
        printf("process 0 da iki degerin toplami = %d \n", local_value + other_value);

    }
    //diger rank id degerine sahip islem bu else blogunda gerceklesecek
    else{
                
        //ikinci islem icin gerekli kodlar burada gerceklesecektir.
        printf("process 1 gerceklesiyor\n");

        //process 0 a process 1 den deger gonderilecek
        MPI_Send(&local_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        //process 0 dan process 1 e veri aktarılacak
        MPI_Recv(&other_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        //2 degerin toplami ekrana yazılır
        printf("process 1 de iki degerin toplami = %d \n", local_value + other_value);
    }

    MPI_Finalize();

    return 0;
}