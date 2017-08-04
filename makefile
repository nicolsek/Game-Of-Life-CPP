all:
	g++ gol.cpp -o gol -std=c++11 -IC:\MinGW\include\ -LC:\MinGW\lib -lsfml-system -lsfml-window -lsfml-graphics

out:
	./gol