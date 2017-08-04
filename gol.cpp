#include <iostream>
#include <cstdlib> //For rand.
#include <ctime> //Seeding for rand.
#include <stdlib.h> //Aghhhh OS-specific.
#include <string.h> 

/* Yay SFML */
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


/*  Rules
	1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
	2. Any live cell with two or three live neighbours lives on to the next generation.
	3. Any live cell with more than three live neighbours dies, as if by overpopulation.
	4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 */

/* Global Variables */
bool isRunning; //If the main-loop isRunning!

/* Global Constants */
constexpr unsigned short golBoardSize = 8; //Size of the golboard.

// golBoard ... The class declaration of the golboard, used for referencing the 'cells' of the board itself and holds useful information.
class golBoard {
	public:
		bool cells [golBoardSize][golBoardSize]; //Creating a [golBoardSize x golBoardSize] matrix. Only states are alive or dead soo boolean!

		unsigned short getNeighbors(unsigned short, unsigned short);
		void generateNewBoard();
		void printArr();
		void update();
} gol;

/*
	[][][]
	[]  [] <-- Format of the returned neighbors except in a sum total of alive form.
	[][][]
 */

// getNeighbors ... Returns all current alive neighbors in a 3x3 fashion.
unsigned short golBoard::getNeighbors(unsigned short coloumn, unsigned short row) {
	unsigned short neighbors;

	return neighbors;
}

// generateNewBoard ... Using the rand and time libraries, seed the random function using the current time and geneate a new board using that!
void golBoard::generateNewBoard() {
	std::srand(std::time(0)); //Seed the rand function using the current time.
	for (auto &row : gol.cells) {
		for (auto &col : row) {
			col = std::rand() % 2;
		}
	}
}

// printArr ... Print the array from the golBoard. 
void golBoard::printArr() {
	for (auto &row : gol.cells) {
		for (auto &col : row) {
			std::cout << col << " ";
		}

		std::cout << std::endl;
	}
}

// update ... Using the rules from Conway's Game Of Life, simulate the current state of the board. 
void golBoard::update() {
	for (int row = 0; row < golBoardSize; row++) {
		for (int col = 0; col < golBoardSize; col++) {
			bool cell = *gol.cells[row, col];
			bool neighbors = gol.getNeighbors(row, col);

			if (&cell && neighbors < 2) { //1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
				cell = 0;
			}

			if (&cell && neighbors > 3) { //3. Any live cell with more than three live neighbours dies, as if by overpopulation.
				cell = 0;
			}

			if (&cell == 0 && neighbors == 3) { //4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
				cell = 1;
			}
		}
	}
}

// main ... The main function, calls for the simulation to update and display the contents of the gol matrix.
int main() {
	//Setting up SFML!
	sf::RenderWindow window(sf::VideoMode(1240, 720), "Conway's Game Of Life");

	gol.generateNewBoard(); //Create a new board using the time as the seed.

	//Main loop.
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) { //Get events from window.
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					std::cout << "Thanks for playing! <3. Written by: Nicole Tusek --> https://github.com/user/nicolsek"; //#ShamelessPlug
			}
		}
	}

	return 0;
}