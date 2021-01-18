prog: main.o mat_io.o backsubst.o gauss.o
	$(cc) -o prog -Wall main.o mat_io.o backsubst.o gauss.o

main.o: main.c gauss.h backsubst.h mat_io.h
	$(cc) main.c
mat_io.o: mat_io.c mat_io.h
	$(cc) -c mat_io.c
backsubst.o: backsubst.c backsubst.h mat_io.h
	$(cc) -c backsubst.c
gauss.o: gauss.c gauss.h gauss.h
	$(cc) -c gauss.c

