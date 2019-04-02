TARGET = build
CC = mpicc
RUN = mpirun
EXE = mpi_hello_world



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
		$(CC) -o $(TARGET)/${EXE} mpi_hello_world.c
		@echo ======derleme islemi basarili ======
		
clean:
		rm -rf $(TARGET)
