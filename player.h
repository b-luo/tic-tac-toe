#pragma once
#include "cell.h"
#include "board.h"
#include <iostream>
//#include <iomanip>
#include <vector>

class Player {
	bool isTurn;
	char piece;
protected:
	Board *gameBoard = nullptr;
	std::vector<Cell *> movesMade;
public:
	Player() {}	// initialize game object first, setting up board before players
	// players share the same board, so simply copy the gameboard pointer
	Player(char piece, Board *gameBoard) : piece{ piece }, gameBoard{ gameBoard }, isTurn{ false } {}
	char getPiece() { return piece;  }
	bool checkTurn() { return isTurn; }
	void setTurn() { isTurn = !isTurn; }
	std::vector<Cell *> getMoves() { return movesMade;  }
	/*
	void displayMoves() {
		std::vector<Cell *>::iterator it;
		for (it = movesMade.begin(); it != movesMade.end(); ++it) {
			Position move = (*it)->getPosition();
			std::cout << setw(8) << move << std::endl;
		}
	}
	*/
	virtual void makeMove() = 0;
	virtual ~Player() {	// delete heap-allocated cell pointers
		for (auto move : movesMade) {
			delete move;
		}
	}
};