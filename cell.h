#pragma once
#include <iostream>

struct Position {
	int x, y;	// (0, 0) starts from leftmost, topmost location on board
};

class Cell {
	Position pos;
	char sym;
	bool containsPiece;
public:
	Cell() : pos{ 0, 0 }, sym{ ' ' }, containsPiece{ false } {}
	Cell(int x, int y) : pos{ x, y }, sym{ ' ' }, containsPiece { false } {}
	Position getPosition() { return pos; }
	void setPosition(int x, int y) { pos.x = x; pos.y = y; }
	void setSym(char sym) {
		this->sym = sym;
		containsPiece = (sym == ' ') ? false : true; 
	}
	char getSym() const { return sym;  }
	bool isOccupied() { return containsPiece;  }
};

// overload output operator for Positions, Cells
std::ostream &operator<<(std::ostream &out, const Position &p);
std::ostream &operator<<(std::ostream &out, const Cell &c);