object: entry.cpp
	g++ -c entry.cpp -lSDL2 -lSDL2_image

game: entry.o
	g++ -g entry.o -lSDL2 -lSDL2_image -o game
	rm *.o

