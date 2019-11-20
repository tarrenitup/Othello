/*
 * MinimaxPlayer.h
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */

#ifndef MINIMAXPLAYER_H
#define MINIMAXPLAYER_H

#include "OthelloBoard.h"
#include "Player.h"
#include <vector>

struct action {
	action(const OthelloBoard& board)
		: resultantBoard(board)
	{
	}
	int column;
	int row;
	int mmValue;
    int depth;
	OthelloBoard resultantBoard;
};

/**
 * This class represents an AI player that uses the Minimax algorithm to play the game
 * intelligently.
 */


class MinimaxPlayer : public Player {
public:


	/**
	 * @param symb This is the symbol for the minimax player's pieces
	 */
	MinimaxPlayer(char symb);

	/**
	 * Destructor
	 */
	virtual ~MinimaxPlayer();

	/**
	 * @param b The board object for the current state of the board
	 * @param col Holds the return value for the column of the move
	 * @param row Holds the return value for the row of the move
	 */
    void get_move(OthelloBoard* b, int& col, int& row);

    /**
     * @return A copy of the MinimaxPlayer object
     * This is a virtual copy constructor
     */
    MinimaxPlayer* clone();

private:



	std::vector<action> successors(const OthelloBoard& state, int depth, char playerSymbol);

	int utility(const OthelloBoard& state);

	action maxValue(const action& state);

	action minValue(const action& state);

	action minimax(const OthelloBoard& state);

};


#endif
