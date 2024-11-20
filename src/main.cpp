#include "raylib.h"
#include "Board.h"

int main (int argc, char *argv[]) {
	Board* board = new Board();

	InitWindow(1000, 1000, "Conway's Game of Life");
	SetTargetFPS(1);

	while (!WindowShouldClose()) {
		board->update();

		BeginDrawing();
		ClearBackground(RAYWHITE);
		board->draw();
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
