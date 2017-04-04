// tictactoe.cpp : Defines the entry point for the console application.
//
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include "stdafx.h"
#include "game.h"
#include <iostream>
#include <string>

using namespace std;

// run the game
int main() {
	/*
	int size;
	cout << "Enter a size for the gameboard: ";
	cin >> size;
	Board *gameBoard = new Board(size);
	cout << *gameBoard << endl;
	
	char nctype;
	cout << "Select your type of piece (X, O): ";
	cin >> nctype;
	NCPlayer ncp{ nctype, gameBoard };

	string command;
	while (true) {
		cout << "Player " << nctype << "'s turn:" << endl;
		ncp.setTurn();
		ncp.makeMove();
		cout << *gameBoard << endl;
		cin >> command;
		if (command == "q") break;
	}
	cout << "Game complete" << endl;
	cout << "List of moves made by player " << nctype << endl;
	ncp.displayMoves();

	delete gameBoard;
	*/

	Game game;
	game.run();
	//_CrtDumpMemoryLeaks();
}

