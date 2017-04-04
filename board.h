#pragma once
#include "cell.h"
#include <vector>

class Board {
	std::vector < std::vector<Cell> > gameBoard;
	int size;
public:
	Board(int);
	int getSize() const;
	std::vector< std::vector<Cell> > getGameBoard() const;
	void updateBoard(char toPlace, Cell toUpdate);
	void resetBoard();
};

std::ostream &operator<<(std::ostream &out, const Board &b);