#include "cplayer.h"
#include <iostream>

using namespace std;

void CPlayer::makeMove() {
	if (!checkTurn()) {
		cout << "Not currently your turn" << endl;
		return;
	}
	Cell *currMove = new Cell(); // holds player's next move
	int x, y;
	cout << "Enter a position to place your piece on: ";
	while (!(cin >> x >> y)) {
		cin.clear();
		cin.ignore(2);
		cout << endl;
		cout << "A position can only have integer coordinates (x, y); please re-enter." << endl;
	}
	cout << "Placing piece onto board..." << endl;
	currMove->setPosition(x, y);
	movesMade.emplace_back(currMove);
	
	// check if update is successful
	try {
		gameBoard->updateBoard(getPiece(), *currMove);
	}
	catch () {

	}
	setTurn();
}