#include "Board.h"
#include "raylib.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

Board::Board() {
    board = new Cell**[x];
    for (int x = 0; x < this->x; x++) {
        board[x] = new Cell*[y];
        for (int y = 0; y < this->y; y++) {
            board[x][y] = new Cell(x * p, y * p, p);
        }
    }
}

Board::~Board() {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete[] board;
}

void Board::draw() {
    // drawing cells
    for (int x = 0; x < this->x; x++) {
        for (int y = 0; y < this->y; y++) {
            if (board[x][y]->isAlive()) {
                board[x][y]->draw();
            }
        }
    }

    // drawing grid lines
    if (drawGrid) {
        // vertical
        for (int i = 1; i < this->x; i++) {
            DrawLine(i * p, 0, i * p, GetScreenHeight(), {0, 0, 0, 255});
        }; // TODO change color to variable
        // horizontal
        for (int i = 1; i < this->y; i++) {
            DrawLine(0, i * p, GetScreenWidth(), i * p, {0, 0, 0, 255});
        }; // TODO change color to variable
    }
}

void Board::update() {
    // updating neighbor counts
    for (int x = 0; x < this->x; x++) {
        for (int y = 0; y < this->y; y++) {
            // iterating every cell
            Cell* currentCell = board[x][y];
            int currentCellNeigh = 0;

            for (auto d : directions) {
                if (x + d[0] >= 0 && x + d[0] < this->x) {
                    if (y + d[1] >= 0 && y + d[1] < this->y) {
                        Cell* otherCell = board[x + d[0]][y + d[1]];
                        if (otherCell->isAlive()) {
                            currentCellNeigh++;
                        }
                    }
                }
            }
            currentCell->setNeighbors(currentCellNeigh);
        }
    }

    // updating cells (dead/alive)
    for (int x = 0; x < this->x; x++) {
        for (int y = 0; y < this->y; y++) {
            board[x][y]->update();
        }
    }

    // updating count of alive cells
    int alive = 0;
    for (int x = 0; x < this->x; x++) {
        for (int y = 0; y < this->y; y++) {
            if (board[x][y]->isAlive()) {
                alive++;
            };
        }
    }
}

int Board::getNumberAlive() {
    int n = 0;
    for (int x = 0; x < this->x; x++) {
        for (int y = 0; y < this->y; y++) {
            if (board[x][y]->isAlive()) {
                n++;
            }
        }
    }

    return n;
}

/*expected file is "matrix" of integers*/
void Board::loadFromFile(const std::string& source) {
    std::ifstream file(source);

    if (!file.is_open()) {
        std::cerr << "Failed to open file " << source << std::endl;
        return;
    }

    int sizeX = 0;
    int sizeY = 0;

    std::string line;

    // get number of columns = xsize
    if (std::getline(file, line)) {
        sizeX = line.size();
        sizeY++;
    }
    // get number of rows = ysize
    while (std::getline(file, line)) {
        sizeY++;
    }

    // allocating memory for array
    int** array = new int*[sizeY];
    for (int y = 0; y < sizeY; y++) {
        array[y] = new int[sizeX];
        for (int x = 0; x < sizeX; x++) {
            array[y][x] = 0;
        }
    }

    // go to the beginning of the file
    file.clear();
    file.seekg(0);

    // read from file and save it to array
    int currentX = 0;
    int currentY = 0;
    while (std::getline(file, line)) {
        currentX = 0;
        for (int i = 0; i < line.size(); i++) {
            array[currentY][currentX] =
                line[i] - '0'; // convert from char to int
            currentX++;
        }
        currentY++;
    }

    // closing the file
    file.close();

    // pass loaded matrix to function load
    load(array, sizeX, sizeY);

    // deallocate memory
    for (int i = 0; i < sizeY; i++) {
        delete[] array[i];
    }
    delete[] array;

    std::cout << "Loading from " << source << " done successfully" << std::endl;
}

void Board::load(int** array, int sizeX, int sizeY) {
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            if (array[y][x] == 1) {
                board[x][y]->setAlive(true);
            }
        }
    }
}
