TARGET = build
CC = mpicc
RUN = mpirun
EXE = blocking



ifndef np
override np = 2
endif

ifndef param
override param = 3
endif

all:	RUN

RUN :	clean build
		@echo ====================================
		@echo ========uygulama basladi============
		${RUN} -np $(np) $(TARGET)/${EXE} $(param)

build:  clean
		mkdir build
		$(CC) -o $(TARGET)/${EXE} blocking.c
		@echo ======derleme islemi basarili ======
		
clean:
		rm -rf $(TARGET)
