#include "Board.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    srand(time(NULL));

    Board* board = new Board();
    FilePathList files = LoadDirectoryFiles("input");
    board->loadFromFile(files.paths[rand() & files.count]);  // loading random file

    InitWindow(1000, 1000, "Conway's Game of Life");
    SetTargetFPS(5);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        board->draw();

        EndDrawing();

        board->update();
        /*WaitTime(0.25);*/
    }

    CloseWindow();

    return 0;
}
