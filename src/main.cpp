//#include "raylib.h"
#include <raylib.h>
#include "Board.h"
#include <iostream>
#include <ostream>

int main (int argc, char *argv[]) {
	Board* board = new Board();

	InitWindow(1000, 1000, "Conway's Game of Life");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		WaitTime(0.5);

		BeginDrawing();
		ClearBackground(WHITE);

		board->draw();
		std::cout << "number of cells alive: " << board->getNumberAlive() << std::endl;

		EndDrawing();

		board->update();
	}

	CloseWindow();

	return 0;
}
