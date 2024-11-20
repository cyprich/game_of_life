#include "Board.h"
#include "raylib.h"

Board::Board() {
	board = new Cell**[x];
	for (int x = 0; x < this->x; x++) {
		board[x] = new Cell*[y];
		for (int y = 0; y < this->y; y++) {
			board[x][y] = new Cell(x*p, y*p, p);
		}
	}

	// oscillator
	board[10][50]->setAlive(true);
	board[10][51]->setAlive(true);
	board[10][52]->setAlive(true);

	// glider
	board[10][10]->setAlive(true);
	board[10][12]->setAlive(true);
	board[11][11]->setAlive(true);
	board[11][12]->setAlive(true);
	board[12][11]->setAlive(true);
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
