
all: game

game: main.cpp
	g++ main.cpp -o game -std=c++0x
