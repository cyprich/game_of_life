#include "Board.h"
#include "raylib.h"

int main(int argc, char* argv[]) {
    Board* board = new Board();

    InitWindow(1000, 1000, "Conway's Game of Life");
    SetTargetFPS(5);

    board->loadFromFile("src/ship1.txt");

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
