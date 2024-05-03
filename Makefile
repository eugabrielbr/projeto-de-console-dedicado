
all: Game.o Mouse.o

	gcc Game.o Mouse.o Main.c -o Main.exe -std=c99 -lintelfpgaup

Game.o: Header.h 
	
	gcc -c Game.c -std=c99 

Mouse.o: Header.h

	gcc -c Mouse.c -std=c99

clean:
	rm -rf *.o Main.exe
