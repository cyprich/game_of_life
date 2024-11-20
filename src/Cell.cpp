#include "Cell.h"
#include <raylib.h>

void Cell::draw() {
	DrawRectangle(x, y, p, p, color);
}

void Cell::update() {
	if (this->isAlive()) {
		alive = n == 2 || n == 3;
	} else {
		alive = n == 3;
	}
}
