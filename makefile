CC = gcc

INCLUDE = -lgdi32

window: window.c
	$(CC) window.c -o window  $(INCLUDE)

clean: 
	rm -f *.o *~ *.out *.exe

