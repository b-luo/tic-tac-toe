#pragma once
#include "board.h"
#include "cplayer.h"
#include "ncplayer.h"
#include <vector>

class Game {
	bool isRunning = false, isOver = false;
	Board *gameBoard = nullptr;
	int numOccupied = 0;
	std::vector<int> scoreTracker;
	CPlayer cp;
	NCPlayer ncp;

	void initialize();
	void displayBoard();
	void displayMovesList();
	void displayScores();	// debug
	void updateScores(Cell *latestMove, bool madeByCp);
	bool isFinished(int toCheck, bool madeByCp);
	void cpMakeMove();
	void ncpMakeMove();
public:
	void run();
	void end();
	~Game();
};