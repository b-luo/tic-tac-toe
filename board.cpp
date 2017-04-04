#include "board.h"
#include <iostream>

using namespace std;

// given a particular board size n, create an n x n gameboard
Board::Board(int size) : size{ size } {
	gameBoard.resize(size);
	// practice using iterators
	for (vector< vector<Cell> >::iterator it = gameBoard.begin(); it != gameBoard.end(); ++it) {
		it->resize(size);
	}
	// initialized n vectors, each of size n
	// now initialize positions of each cell
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			gameBoard[i][j] = Cell{ i, j };
		}
	}
}

int Board::getSize() const { return size;  }

vector< vector<Cell> > Board::getGameBoard() const { return gameBoard;  }

// after player has made a move by placing their piece on the given cell,
// update the state of the board
void Board::updateBoard(char toPlace, Cell toUpdate) {
	Position pos = toUpdate.getPosition();
	cout << "Updating position (" << pos.x << ", " << pos.y << ")..." << endl;
	if (pos.x < 0 || pos.y < 0 || pos.x >= size || pos.y >= size) {
		cout << "The given position is out of range, each coordinate must lie within [0, " <<
			size << ")" << endl;
		return;
	}
	if (gameBoard[pos.x][pos.y].isOccupied()) {
		cout << pos << " is occupied" << endl;
		return;
	}
	gameBoard[pos.x][pos.y].setSym(toPlace);
}

void Board::resetBoard() {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			gameBoard[i][j].setSym(' ');
		}
	}
}

ostream &operator<<(ostream &out, const Board &b) {
	/*
	vector< vector<Cell> >::const_iterator row;
	vector<Cell>::const_iterator col;
	for (row = b.getGameBoard().begin(); row != b.getGameBoard().end(); ++row) {
		for (col = row->begin(); col != row->end(); ++col) {
			out << *col;	// display symbol of each Cell
		}
		out << endl;
	}
	*/
	for (int i = 0; i < b.getSize(); ++i) {
		for (int j = 0; j < b.getSize(); ++j) {
			if (j == 0) {
				out << " ";
			}
			out << b.getGameBoard()[i][j];
			if (j != b.getSize() - 1) {
				out << " | ";
			}
		}
		out << endl;
		if (i != b.getSize() - 1) {
			for (int k = 0; k < (4 * b.getSize() - 1); ++k) {
				out << (((k + 1) % 4 == 0) ? "+" : "-");
			}
		}
		out << endl;
	}
	return out;
}