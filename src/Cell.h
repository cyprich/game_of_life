#include "raylib.h"
#include <cstdlib>
#include <iostream>

class Cell {
private:
	int x, y, p, n;
	int alive = rand() % 2;
	/*int alive = false;*/
	/*int alive = true;*/
	Color color = {0,0,0, 255};  // TODO maybe change this
public:
	Cell(): x(0), y(0), p(10) {};
	Cell(int posX, int posY, int size): x(posX), y(posY), p(size) {};
	~Cell();

	void update();
	void draw();

	void setNeighbors(int n) {this->n = n; setAlive(); };
	void setAlive();

	int isAlive() {return alive;};
	int getX() { return x; };
	int getY() { return y; };
	int getP() { return p; };
};
