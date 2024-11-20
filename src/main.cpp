#include <iostream>
#include "raylib.h"
#include "Board.h"

int main (int argc, char *argv[]) {
	std::cout << "Conway's Game of Life" << std::endl;
	InitWindow(1000, 1000, "Conway's Game of Life");
	SetTargetFPS(60);

	Board* board = new Board();

	while (!WindowShouldClose()) {
		board->update();

		BeginDrawing();
		board->draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
