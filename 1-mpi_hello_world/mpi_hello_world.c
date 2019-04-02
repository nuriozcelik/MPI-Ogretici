///////////////////////////////////////////////////////////
//                      mpi_hello_world.c                //
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
    //degerlerin yazdirilmasi
    printf("Islem #%d den merhaba :))\n", rank);
    if(rank == 0){
        //rank degeri sifir olan islem icinde ekrana tum islemin size degeri yazilir.
        printf("islemin size degeri #%d dir. \n", size);
    }
    //bitir
    MPI_Finalize();

    return 0;
}