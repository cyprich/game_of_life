#include "Board.h"
#include <raylib.h>

void Cell::draw() {
	DrawRectangle(x, y, p, p, color);
}
