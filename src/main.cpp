#include <iostream>
#include "raylib.h"

int main (int argc, char *argv[]) {
	std::cout << "Conway's Game of Life" << std::endl;
	InitWindow(800, 800, "Conway's Game of Life");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
