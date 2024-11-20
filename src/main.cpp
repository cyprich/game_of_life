#include "raylib.h"
#include "Board.h"

int main (int argc, char *argv[]) {
	Board* board = new Board();

	InitWindow(1000, 1000, "Conway's Game of Life");
	SetTargetFPS(10);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(WHITE);

		board->draw();

		EndDrawing();

		board->update();

		/*WaitTime(0.25);*/
	}

	CloseWindow();

	return 0;
}
