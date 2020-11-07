CC = gcc

INCLUDE = -lgdi32

window: windowRunner.c windowRunnerUtils.o
	$(CC) windowRunnerUtils.o windowRunner.c -o window  $(INCLUDE)

windowRunnerUtils.o: windowRunnerUtils.c windowRunnerUtils.h
	$(CC) -c windowRunnerUtils.c  $(INCLUDE)

clean: 
	rm -f *.o *~ *.out *.exe

