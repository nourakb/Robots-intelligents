CC := gcc

CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm
	
main: main.o fonction.o
	$(CC) $^ -o $@ $(CFLAGS)

main.o:main.c fonction.h constante.h
	$(CC) -c main.c $(CFLAGS)
fonction.o:fonction.c fonction.h constante.h
	$(CC) -c fonction.c $(CFLAGS)

clean:
	rm *.o 
	
	
	
	


