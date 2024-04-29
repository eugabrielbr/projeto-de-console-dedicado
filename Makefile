all: Game.o Mouse.o

	gcc Game.o Mouse.o Main.c -o Main.exe

funcs.o: Header.h 
	
	gcc -c Game.c Mouse.c

clean:
	rm -rf *.o Main.exe