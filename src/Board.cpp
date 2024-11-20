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
	const int directions[8][2] = {
		{-1, -1},
		{-1,  0},
		{-1,  1},
		{ 0, -1},
		{ 0,  1},
		{ 1, -1},
		{ 1,  0},
		{ 1,  1}
	};

	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			// iterating every cell
			int n = 0;

			for (auto d : directions) {
				// iterating every direction
				// checking if index is not out of range (0 to number of cells)
				if (x+d[0] >= 0 && x+d[0] < this->x && y+d[1] >= 0 && y+d[1] < this->y) {
					// checking if cell is alive, then adding neighbor count
					if (board[x+d[0]][y+d[1]]->isAlive()) {n++; };
				}
			}
			// setting new number of neighbors to current cell
			board[x][y]->setNeighbors(n);
		}
	}
}
