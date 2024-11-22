#pragma once
#include "Cell.h"

class Board {
private:
	int x = 100;
	int y = 100;
	int p = 1000/x;  // TODO change 1000 to global variable
	bool drawGrid = false;
  const int directions[8][2] = {
		{-1, -1},
		{-1,  0},
		{-1,  1},
		{ 0, -1},
		{ 0,  1},
		{ 1, -1},
		{ 1,  0},
		{ 1,  1}
	};

	Cell*** board;
public:
	Board();
	~Board();

	void update();
	void draw();
  void loadFromFile(const std::string& source);
  void load(int** array, int sizeX, int sizeY);

	int getNumberAlive();
};
