CC = gcc

INCLUDE = -lgdi32

window: windowRunner.c windowRunnerUtils.o imageUtils.o
	$(CC) windowRunnerUtils.o imageUtils.o windowRunner.c -o window  $(INCLUDE)

windowRunnerUtils.o: windowRunnerUtils.c windowRunnerUtils.h
	$(CC) -c windowRunnerUtils.c  $(INCLUDE)

imageUtils.o: imageUtils.c imageUtils.h
	$(CC) -c imageUtils.c  $(INCLUDE)

clean: 
	rm -f *.o *~ *.out *.exe

