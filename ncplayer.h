#pragma once
#include "player.h"
#include "board.h"

// non-computer player
class NCPlayer : public Player {
public:
	NCPlayer() {}
	NCPlayer(char piece, Board *gameBoard) : Player{ piece, gameBoard } {}
	void makeMove();
};