#pragma once

class Board {
private:
	int x = 100;
	int y = 100;
	int p = 1000/x;  // TODO change 1000 to global variable
	bool drawGrid = true;
public:
	Board(){};
	~Board(){};
	void update() {};
	void draw();
};
