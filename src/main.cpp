#include "Board.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    srand(time(NULL));
    Board* board = new Board();

    if (argc == 1) {  // if file path is not specified, load random file
        FilePathList files = LoadDirectoryFiles("input");
        board->loadFromFile(
            files.paths[rand() & files.count] // loading random file
	); 
    } else { 
	board->loadFromFile(argv[1]);
    }

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

    delete board;

    return 0;
}
