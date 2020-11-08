CC = gcc -Wall

INCLUDE = -lgdi32

window: windowRunner.c windowRunnerUtils.o imageUtils.o
	$(CC) imageUtils.o windowRunnerUtils.o  windowRunner.c -o window  $(INCLUDE)

windowRunnerUtils.o: windowRunnerUtils.c windowRunnerUtils.h imageUtils.o 
	$(CC) -c imageUtils.o windowRunnerUtils.c $(INCLUDE)

imageUtils.o: imageUtils.c imageUtils.h
	$(CC) -c imageUtils.c  $(INCLUDE)

clean: 
	rm -f *.o *~ *.out *.exe

