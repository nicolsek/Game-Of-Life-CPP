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

/* Global Constants */
constexpr unsigned char GOLBOARD_SIZE = 80; //Size of the golboard.
constexpr unsigned char WINDOW_FPS = 30; //Frame rate for window.

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;


// golBoard ... The class declaration of the golboard, used for referencing the 'cells' of the board itself and holds useful information.
class golBoard {
	public:
		bool cells[GOLBOARD_SIZE][GOLBOARD_SIZE]; //Creating a [GOLBOARD_SIZE x GOLBOARD_SIZE] matrix. Only states are alive or dead soo boolean!

		unsigned short getNeighbors(unsigned int, unsigned int);
		void generateNewBoard();
		void printArr();
		void printArr3(unsigned int, unsigned int);
		void update();
} gol;

/*
	[][][]
	[]  [] <-- Format of the returned neighbors except in a sum total of alive form.
	[][][]
 */

// getNeighbors ... Returns all current alive neighbors in a 3x3 fashion.
unsigned short golBoard::getNeighbors(unsigned int row, unsigned int col) {
	unsigned short neighbors = 0; //Neighbors start at 0.

	/* Using a 3x3 search of the matrix */
	for (char neighRow = -1; neighRow < 2; neighRow++) {
		for (char neighCol = -1; neighCol < 2; neighCol++) {
			/* Checking bounds */
			if (neighRow + row >= 0 && neighCol + col >= 0) {
				neighbors += gol.cells[row + neighRow][col + neighCol];
			}
		}
	}

	neighbors -= gol.cells[row][col]; //Get rid of the center piece as a neighbor.

	return neighbors;
}

// generateNewBoard ... Using the rand and time libraries, seed the random function using the current time and geneate a new board using that!
void golBoard::generateNewBoard() {
	std::srand(std::time(0)); //Seed the rand function using the current time.
	for (auto &row : gol.cells) {
		for (auto &col : row) {
			col = std::rand() % 10 && 1;
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

//printArr3 ... Print the array from the golBoard in 3x3 sections to check neighbors. 
void golBoard::printArr3(unsigned int row, unsigned int col) {
	/* Using a 3x3 search of the matrix */
	for (int neighRow = -1; neighRow < 2; neighRow++) {
		for (int neighCol = -1; neighCol < 2; neighCol++) {
			/* Checking bounds */
			if (neighRow + row >= 0 && neighCol + col >= 0) {
				std::cout << gol.cells[neighRow + row][neighCol + col] << " ";
			}
		}

		std::cout << std::endl;
	}
}

// update ... Using the rules from Conway's Game Of Life, simulate the current state of the board. 
void golBoard::update() {
	for (int row = 0; row < GOLBOARD_SIZE; row++) {
		for (int col = 0; col < GOLBOARD_SIZE; col++) {
			bool cell = gol.cells[row][col]; //I hope this is how pointers work.
			
			unsigned int neighbors = gol.getNeighbors(row, col);

			if (cell && neighbors < 2) { //1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
				gol.cells[row][col] = 0;
			}

			if (cell && neighbors > 3) { //3. Any live cell with more than three live neighbours dies, as if by overpopulation.
				gol.cells[row][col] = 0;
			}
			
			if (!cell && neighbors == 3) {
				gol.cells[row][col] = 1;
			}
		}
	}
}

//draw ... The draw function! Draws stuff to the screen using SFML.
void draw(sf::RenderWindow &window) {
	window.clear(); //Clear the current state of the window before drawing to it.

	/* Drawing the board! */

	const unsigned int width = (WINDOW_WIDTH / GOLBOARD_SIZE); //The width of the cell to be drawn.
	const unsigned int height = (WINDOW_HEIGHT / GOLBOARD_SIZE); //The height of the cell to be drawn.

	for (unsigned int row = 0; row < GOLBOARD_SIZE; row++) {
		for (unsigned int col = 0; col < GOLBOARD_SIZE; col++) {
			sf::RectangleShape rect(sf::Vector2f(width, height)); //The current rectangle shape.			

			unsigned int offsetX = (WINDOW_WIDTH / GOLBOARD_SIZE) * row; //Defining the offset of where to draw the x position of the square to the screen.
			unsigned int offsetY = (WINDOW_HEIGHT / GOLBOARD_SIZE) * col; //Defining the offset of where to draw the y position of the square to the screen.

			if (gol.cells[row][col] == 0) { //If the cell is dead display red.
				rect.setFillColor(sf::Color::Black);
			}
			
			rect.setPosition(offsetX, offsetY); //Set the position of the current quad to the correct offset.
			rect.setOutlineColor(sf::Color::Red); //Draw a border around cells.
			rect.setOutlineThickness(1); //Draw a border around cells.
		
			window.draw(rect);
		}
	}


	window.display(); //Display the OpenGL context :)
}

// main ... The main function, calls for the simulation to update and display the contents of the gol matrix.
int main() {
	//Setting up SFML!
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Conway's Game Of Life"); //Creating the window context.
	window.setFramerateLimit(WINDOW_FPS); //Limit the FPS to the desired frame rate.

	window.setActive(); //Set the window to the active state to allow OpenGL to draw to it. :)

	gol.generateNewBoard(); //Create a new board using the time as the seed.

	//gol.printArr();

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

		gol.update(); //Update the current state of the array using the rule set.
	
		draw(window); //Call the draw function to draw the stuffs to the screen!
	}

	return 0;
}