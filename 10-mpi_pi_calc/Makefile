TARGET = build
CC = mpicc
RUN = mpirun
EXE = calc_pi



ifndef np
override np = 2
endif


all:	RUN

RUN :	clean build
		@echo ====================================
		@echo ========uygulama basladi============
		${RUN} -np $(np) $(TARGET)/${EXE}

build:  clean
		mkdir build
		$(CC) -o $(TARGET)/${EXE} mpi_calc.c
		@echo ======derleme islemi basarili ======
		
clean:
		rm -rf $(TARGET)
