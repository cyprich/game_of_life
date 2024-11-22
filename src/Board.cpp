#include "Board.h"
#include "raylib.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

Board::Board() {
	board = new Cell**[x];
	for (int x = 0; x < this->x; x++) {
		board[x] = new Cell*[y];
		for (int y = 0; y < this->y; y++) {
			board[x][y] = new Cell(x*p, y*p, p);
		}
	}

	// oscillator
	/*board[10][50]->setAlive(true);*/
	/*board[10][51]->setAlive(true);*/
	/*board[10][52]->setAlive(true);*/

	// glider
	/*board[10][10]->setAlive(true);*/
	/*board[10][12]->setAlive(true);*/
	/*board[11][11]->setAlive(true);*/
	/*board[11][12]->setAlive(true);*/
	/*board[12][11]->setAlive(true);*/
}

void Board::draw() {
	// drawing cells
	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			if (board[x][y]->isAlive()) {
				board[x][y]->draw();
			}
		}
	}

	//drawing grid
	if (drawGrid) {
		// vertical
		for (int i = 1; i < this->x; i++) {DrawLine(i*p, 0, i*p, GetScreenHeight(), {0,0,0,255}); };  // TODO change color to variable
		// horizontal
		for (int i = 1; i < this->y; i++) {DrawLine(0, i*p, GetScreenWidth(), i*p, {0,0,0,255}); };  // TODO change color to variable
	}
}

void Board::update() {
	// updating neighbor counts
	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			// iterating every cell
			Cell* currentCell = board[x][y];
			int currentCellNeigh = 0;

			for (auto d : directions) {
				if (x+d[0] >= 0 && x+d[0] < this->x) {
					if (y+d[1] >= 0 && y+d[1] < this->y) {
						Cell* otherCell = board[x+d[0]][y+d[1]];
						if (otherCell->isAlive()) {
							currentCellNeigh++;
						}
					}
				}
			}
			currentCell->setNeighbors(currentCellNeigh);
		}
	}

	// updating cells (dead/alive)
	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			board[x][y]->update();
		}
	}

	// updating count of alive cells
	int alive = 0;
	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			if (board[x][y]->isAlive()) {alive++;};
		}
	}
}


int Board::getNumberAlive() {
	int	n = 0;
	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			if (board[x][y]->isAlive()) {n++;}
		}
	}
	
	return n;
}

/*expected file is "matrix" of integers*/
void Board::loadFromFile(const std::string& source) {
	std::ifstream file(source);

	if (!file.is_open()) {
		std::cerr << "Failed to open file " << source << std::endl;
		return;
	}

	int xSize = 0;
	int ySize = 0;

	std::string line;

	// get number of columns = xsize
	if (std::getline(file, line)) {
		xSize = line.size();
		ySize++;
	}
	// get number of rows = ysize
	while (std::getline(file, line)) {
		ySize++;
	}

	// allocating memory for array
	int** array = new int*[ySize];
	for (int y = 0; y < ySize; y++) {
		array[y] = new int[xSize];
	}

	// go to the beginning of the file
	file.clear();
	file.seekg(0);

	// read from file and save it to array
	int currentX = 0;
	int currentY = 0;
	while (std::getline(file, line)) {
		for (auto l : line) {
			array[currentY][currentX] = l;
			currentX++;
		}
		currentY++;
	}

	// closing the file
	file.close();


	// pass loaded matrix to function load
	load(array, xSize, ySize);

	// deallocate memory
	for (int i = 0; i < ySize; i++) {
		delete[] array[i];
	}

	delete[] array;
	
	std::cout << "Loading from " << source << " done successfully" << std::endl;
}

void Board::load(int** array, int sizeX, int sizeY) {
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			if (array[y][x] != 0) {
				board[x][y]->setAlive(true);
			}
		}
	}
}
