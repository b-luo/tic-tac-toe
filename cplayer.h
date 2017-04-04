#pragma once
#include "player.h"

// computer player
class CPlayer: public Player {
public:
	CPlayer() {}
	CPlayer(char piece, Board *gameBoard) : Player{ piece, gameBoard } {}
	void makeMove();
};