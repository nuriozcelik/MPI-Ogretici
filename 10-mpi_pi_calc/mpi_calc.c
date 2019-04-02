#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char **argv){
    //USED FOR CALCULATE ERROR
    const double REAL_PI = 3.141592653589793238462643383;

    //INIT MPI
    MPI_Init(&argc, &argv);

    //PROCESS SIZE AND UNIQ ID
    int size, rank;

    //CALCULATION ACCURACY 
    int accuracy;

    //GET PROCESS SIZE AND RANK
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    //GETTING ARGUMENTS FROM USER
    if(rank == 0){
        printf("Enter the calculation accuracy or press 0 for exit...\n");
        scanf("%d", &accuracy);
        if(accuracy == 0){
            return 0;
        }
    }

    //SEND VARIABLE TO OTHER PROCESS
    MPI_Bcast(&accuracy, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //SYNCHRONISATION 1
    MPI_Barrier(MPI_COMM_WORLD);

    //START CHRONOMETER FOR CALCULATING PROCESS TIME
    double time = -MPI_Wtime();

    //PROCESS BUFFER
    double buffer[2] = {0};
    for(int i = 1; i <= accuracy; i++)
    {
        buffer[0] += (double)((1.0/((4.0*(double)i)-1.0)));
        buffer[1] += (double)(1.0/((4.0*(double)i)+1.0));
    }

    //SUM OPERATION BUFFER
    double recvBuff[2] = {0};
    MPI_Reduce(&buffer, &recvBuff, 2, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    //SYNCHRONISATION 2
    MPI_Barrier(MPI_COMM_WORLD);

    //STOP CHRONOMETER
    time += MPI_Wtime();

    //CALCULATE FINAL TIME TO ALL PROCESS
    double final_time;
    MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    //PRINT RESULT ON PROCESS O
    if(rank == 0){
        double pi;
        pi = 4 * ((1 + recvBuff[1]/size) - recvBuff[0]/size);
        printf("============================================ \n");
        printf("  \n");
        printf("Total time for calculate = %f s.\n",final_time);
        printf("Pi Number               ~= %.16f \n", pi);
        printf("ERROR                   ~= %.16f \n", pi - REAL_PI);
        printf("  \n");
        printf("============================================ \n");
    }
    
    //FIN
    MPI_Finalize();
    return 0;
}