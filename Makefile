game: game.o board.o
	gcc game.o board.o -Wall -o game

game.o: game.c board.h
	gcc game.c -Wall -c

board.o:
	gcc board.c -Wall -c

clean:
	rm *.o
