#include "game.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void Game::initialize() {
	int size;
	cout << "Enter a size for the board: ";
	cin >> size;
	gameBoard = new Board{ size };

	// scoretracker records scores for each row, column and diagonal (2); each score initially 0
	// scores indicate 
	scoreTracker.resize(2 * size + 2);

	// construct players - choose type of piece
	char nctype, ctype;
	cout << "Select your type of piece, either X or O: ";
	cin >> nctype;
	ncp = NCPlayer { nctype, gameBoard };

	ctype = (nctype == 'X') ? 'O' : 'X';
	cp = CPlayer { ctype, gameBoard };

	isRunning = true;
}

void Game::displayBoard() {
	cout << *gameBoard << endl;
}

void Game::displayMovesList() {
	cout << "Player " << ncp.getPiece() << " | Player " << cp.getPiece() << endl;
	cout << "-------------------" << endl;
	vector<Cell *>::iterator it, it2;
	for (it = ncp.getMoves().begin(), it2 = cp.getMoves().begin(); (it != ncp.getMoves().end() &&
		it2 != cp.getMoves().end()); ++it, ++it2) {
		Position ncMove = (*it)->getPosition(), cMove = (*it2)->getPosition();
		cout << setw(8) << ncMove << " | " << setw(8) << cMove << endl;
	}
}

void Game::displayScores() {
	int boardSize = gameBoard->getSize();
	for (int i = 0; i < scoreTracker.size(); ++i) {
		if (i < boardSize) {
			cout << "ROW " << i << ": " << scoreTracker.at(i) << endl;
		}
		else if (i >= boardSize && i < 2 * boardSize) {
			cout << "COL " << i - boardSize << ": " << scoreTracker.at(i) << endl;
		}
		else {
			cout << "DIAG " << i - 2 * boardSize << ": " << scoreTracker.at(i) << endl;
		}
	}
}

// update scores held in the score tracker accordingly based on whether the latest move was made
// by a computer player or a non-computer player
void Game::updateScores(Cell *latestMove, bool madeByCp) {
	// prevent score from being adjusted when player attempted to move on occupied cell
	/*
	if (madeByCp) {	// the symbol of the player will differ from the one the cell contains
		if (latestMove->getSym() != cp.getPiece()) return;
	}
	else {
		if (latestMove->getSym() != ncp.getPiece()) return;
	}
	*/
	// position of the piece most recently placed on the board
	Position lastUpdated = latestMove->getPosition();

	// since the nullptr check was made before, the coordinates of lastUpdated will be valid
	int row = lastUpdated.x, col = lastUpdated.y;

	int inc = gameBoard->getSize();
	// indices of score tracker corresponding to the row, column of the updated position
	int rowIndex = row, colIndex = col + inc;

	// score of -1 indicates computer player made a move & -1 for non-computer player
	int scoreAdjust = (madeByCp) ? -1 : 1;

	scoreTracker.at(rowIndex) += scoreAdjust;
	isOver = isFinished(rowIndex, madeByCp);
	cout << "Score for row " << row << ": " << scoreTracker.at(row) << endl;

	scoreTracker.at(colIndex) += scoreAdjust;
	cout << "Score for col " << col << ": " << scoreTracker.at(col + inc) << endl;
	if (!isOver) isOver = isFinished(colIndex, madeByCp);
	if (row == col) { // update first diagonal (\)
		scoreTracker.at(2 * inc) += scoreAdjust;
		cout << "Score for diag 0: " << scoreTracker.at(2 * inc) << endl;
		if (!isOver) isOver = isFinished(2 * inc, madeByCp);
	}
	if (row == (inc - col - 1)) {	// update second diagonal (/) - piece could be placed on both diagonals
		scoreTracker.at(2 * inc + 1) += scoreAdjust;
		cout << "Score for diag 1: " << scoreTracker.at(2 * inc + 1) << endl;
		if (!isOver) isOver = isFinished(2 * inc + 1, madeByCp);
	}
}

// need to check for tie condition
// need to check if board is full & no winner

// determine based on the latest move made whether or not a player has won the game
// toCheck is the index corresponding to the row, column or diagonal whose score was just updated
bool Game::isFinished(int toCheck, bool madeByCp) {
	// if a row, column or diagonal has the needed score, then it is full (only contains pieces
	// of a single type)
	int inc = gameBoard->getSize();
	int cpScoreNeeded = -inc, ncpScoreNeeded = inc;
	
	if (madeByCp) {
		if (scoreTracker.at(toCheck) == cpScoreNeeded) {
			cout << "Player " << cp.getPiece() << " has won!" << endl;
			return true;
		}
		return false;
	}
	else {
		if (scoreTracker.at(toCheck) == ncpScoreNeeded) {
			cout << "Player " << ncp.getPiece() << " has won!" << endl;
			return true;
		}
		return false;
	}
}

void Game::cpMakeMove() {
	cp.makeMove();
	// compute the score for the appropriate row, column, diagonal resulting from the move
	
	// nullptr case: player makes move when it's not their turn
	Cell *lastMoveMade = (!cp.getMoves().empty()) ? cp.getMoves().back() : nullptr;

	if (lastMoveMade == nullptr) {
		ncp.setTurn();
		return;
	}
	displayBoard();
	updateScores(lastMoveMade, true);
	ncp.setTurn();	// ready the non-computer player to make their move
}

void Game::ncpMakeMove() {
	ncp.makeMove();
	// compute the score for the appropriate row, column, diagonal resulting from the move

	// nullptr case: player makes move when it's not their turn
	Cell *lastMoveMade = (!ncp.getMoves().empty()) ? ncp.getMoves().back() : nullptr;

	if (lastMoveMade == nullptr) {
		cp.setTurn();
		return;
	}
	displayBoard();
	updateScores(lastMoveMade, false);
	
	cp.setTurn();
}

void Game::run() {
	initialize();

	cout << "Select whether you want to go first (y/n): ";
	string command;
	cin >> command;
	if (command == "y") {
		cout << "Player " << ncp.getPiece() << " will go first." << endl;
		ncp.setTurn();
	}
	else {
		cout << "Player " << cp.getPiece() << " will go first." << endl;
		cp.setTurn();
	}

	cout << "Here's what the board looks like:" << endl;
	displayBoard();

	while (isRunning) {
		//displayBoard();
		// alternate between each player taking a move

		cout << "Player " << ncp.getPiece() << "'s move: " << endl;
		ncpMakeMove();
		if (isOver) break;
		//cp.setTurn();
		//displayBoard();
		cout << "Player " << cp.getPiece() << "'s move: " << endl;
		cpMakeMove();
		if (isOver) break;
		//ncp.setTurn();
	}
	end();
}

void Game::end() {
	cout << "Game complete: excellent work!" << endl;
	cout << "Displaying score table:" << endl;
	displayScores();
	cout << "Here are the set of moves made by each player:" << endl;
	displayMovesList();
}

Game::~Game() {
	delete gameBoard;
}