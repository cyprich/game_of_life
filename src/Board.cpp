#include "Board.h"
#include "raylib.h"

void Board::draw() {
	for (int x = 0; x < this->x; x++) {
		for (int y = 0; y < this->y; y++) {
			DrawRectangle(x*p, y*p, p-drawGrid, p-drawGrid, {255,255,255,255});
		}
	}
}
